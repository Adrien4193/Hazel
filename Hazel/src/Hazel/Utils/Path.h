#pragma once

namespace Hazel
{
    class Path
    {
    private:
        const std::string &path;

    public:
        constexpr Path(const std::string &path)
            : path(path)
        {
        }

        inline std::string GetDirectory() const
        {
            size_t offset = path.find_last_of("/\\");
            return offset == std::string::npos ? "" : path.substr(0, offset);
        }

        inline std::string GetFilename() const
        {
            size_t start = path.find_last_of("/\\");
            start = start == std::string::npos ? 0 : start + 1;
            size_t end = path.rfind('.');
            end = end == std::string::npos ? path.size() : end;
            return path.substr(start, (end > start ? end : path.size()) - start);
        }

        inline std::string GetExtension() const
        {
            size_t offset = path.rfind('.');
            return offset == std::string::npos ? "" : path.substr(offset + 1, path.size() - offset);
        }
    };
}