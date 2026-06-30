#pragma once

enum class LogLevel { Trace, Debug, Info, Warn, Error };

class Log {
public:
    template <typename... Args>
    struct LogMessage {
        std::format_string<Args...> fmt;
        std::source_location loc;

        consteval LogMessage(const char* s, const std::source_location& l = std::source_location::current())
        : fmt(s), loc(l) {}
    };

#ifdef NDEBUG
    static inline LogLevel min_level = LogLevel::Info;
#else
    static inline LogLevel min_level = LogLevel::Trace;
#endif

    template <typename... Args>
    static void Info(LogMessage<std::type_identity_t<Args>...> msg, Args&&... args) {
        Print(LogLevel::Info, "INFO", msg.fmt, msg.loc, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Warn(LogMessage<std::type_identity_t<Args>...> msg, Args&&... args) {
        Print(LogLevel::Warn, "WARN", msg.fmt, msg.loc, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Error(LogMessage<std::type_identity_t<Args>...> msg, Args&&... args) {
        Print(LogLevel::Error, "ERROR", msg.fmt, msg.loc, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Debug(LogMessage<std::type_identity_t<Args>...> msg, Args&&... args) {
        Print(LogLevel::Debug, "DEBUG", msg.fmt, msg.loc, std::forward<Args>(args)...);
    }

private:
    static inline std::mutex log_mutex;

    template <typename... Args>
    static void Print(LogLevel level, std::string_view prefix, std::format_string<Args...> fmt,
                      const std::source_location& loc, Args&&... args) {
        if (level < min_level) return;

        std::string msg = std::format(fmt, std::forward<Args>(args)...);

        std::string_view file = loc.file_name();
        if (auto pos = file.find_last_of("/\\"); pos != std::string_view::npos) {
            file.remove_prefix(pos + 1);
        }

        std::lock_guard lock(log_mutex);
        std::cout << std::format("[{}] [{}:{}] {}\n", prefix, file, loc.line(), msg);
    }
};
