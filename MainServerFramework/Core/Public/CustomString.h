#pragma once


SPACE_BEGIN(Core)

template<class T>
using STRING = std::basic_string<T, std::char_traits<T>, USTLAllocator<T>>;

template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
class CustomString : public STRING<TChar> {
    using ChangeType = std::conditional<std::is_same_v<TChar, char>, STRING<char>, STRING<wchar_t>>;
public:
    using CUSSTRING = CustomString<TChar, TString>;
    CustomString() : STRING<TChar>() {}
    CustomString(const TString& str) : STRING<TChar>(str) {}
    CustomString(const TChar* str) : STRING<TChar>(str) {}
    CustomString(const CustomString& str) : STRING<TChar>(str) {}
    CustomString(const STRING<TChar>& str) :STRING<TChar>(str) {}
    CustomString(TString&& str) noexcept : STRING<TChar>(std::move(str)) {}
    CustomString(STRING<TChar>&& str) noexcept : STRING<TChar>(std::move(str)) {}
    CustomString(CUSSTRING&& other) noexcept : STRING<TChar>(std::move(other)) {}

    operator const TChar* () const { return this->c_str(); }
    operator const TString& () const { return *this; }

    explicit operator bool() const { return !this->empty(); }

    TChar& operator[](unsigned long long  index) { return STRING<TChar>::operator[](index); }

    bool operator<(const CUSSTRING& str) const {
        return this->compare(str.c_str()) < 0;
    }

    bool operator==(const TChar* rhs) const { return this->compare(rhs) == 0; }
    bool operator!=(const TChar* rhs) const { return this->compare(rhs) != 0; }

    bool operator==(TChar ch) const { return !this->empty() && this->at(0) == ch; }
    bool operator!=(TChar ch) const { return this->empty() || this->at(0) != ch; }
};

template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
bool operator ==(const TString& _str1, const CustomString<TChar, TString>& _str2) { return _str2.contains(_str1.c_str()); }
template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
bool operator !=(const TString& _str1, const CustomString<TChar, TString>& _str2) { return false == _str2.contains(_str1.c_str()); }

template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
bool operator ==(const TChar* _str1, const CustomString<TChar, TString>& _str2) { return _str2.contains(_str1); }

template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
bool operator !=(const TChar* _str1, const CustomString<TChar, TString>& _str2) { return false == _str2.contains(_str1); }

template<class TChar, class TString>
    requires CheckCustomString<TChar, TString>
CustomString<TChar, TString> operator+(const TChar* _pChar, CustomString<TChar, TString> _strText)
{
    return _strText.append(_pChar);
}

template<typename TChar, typename TString>
    requires CheckCustomString<TChar, TString>
static std::basic_ostream<TChar>& operator<<(std::basic_ostream<TChar>& os, const CustomString<TChar, TString>& str) {
    os << static_cast<const TChar*>(str);
    return os;
}

using String = std::basic_string<char, std::char_traits<char>, Core::USTLAllocator<char>>;
using Wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, Core::USTLAllocator<wchar_t>>;

using String = std::basic_string<char, std::char_traits<char>, USTLAllocator<char>>;
using Wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, USTLAllocator<wchar_t>>;

namespace Internal {

    // 부호 없는 정수 -> 버퍼로 역순 변환
    template<typename _Elem, typename _UTy>
    _Elem* _UIntegral_to_buff(_Elem* _RNext, _UTy _Val) {
        do {
            *--_RNext = static_cast<_Elem>('0' + (_Val % 10));
            _Val /= 10;
        } while (_Val != 0);
        return _RNext;
    }
}

// Core::String / Core::Wstring 반환용
template <class _Elem, class _Ty>
[[nodiscard]] std::basic_string<_Elem, std::char_traits<_Elem>, USTLAllocator<_Elem>>
_Integral_to_string(const _Ty _Val) {
    static_assert(std::is_integral_v<_Ty>, "_Ty must be integral");
    using _UTy = std::make_unsigned_t<_Ty>;

    _Elem _Buff[21]; // -2^63 ~ 2^64 - 1 + '\0'
    _Elem* const _Buff_end = std::end(_Buff);
    _Elem* _RNext = _Buff_end;
    const auto _UVal = static_cast<_UTy>(_Val);

    if constexpr (std::is_signed_v<_Ty>) {
        if (_Val < 0) {
            _RNext = Internal::_UIntegral_to_buff(_RNext, 0 - _UVal);
            *--_RNext = static_cast<_Elem>('-');
        }
        else {
            _RNext = Internal::_UIntegral_to_buff(_RNext, _UVal);
        }
    }
    else {
        _RNext = Internal::_UIntegral_to_buff(_RNext, _UVal);
    }

    return std::basic_string<_Elem, std::char_traits<_Elem>, USTLAllocator<_Elem>>(_RNext, _Buff_end);
}

// 편의 함수
inline String ToString(int val) { return _Integral_to_string<char>(val); }
inline String ToString(unsigned int val) { return _Integral_to_string<char>(val); }
inline String ToString(long val) { return _Integral_to_string<char>(val); }
inline String ToString(unsigned long val) { return _Integral_to_string<char>(val); }
inline String ToString(long long val) { return _Integral_to_string<char>(val); }
inline String ToString(unsigned long long val) { return _Integral_to_string<char>(val); }
inline String ToString(bool val) { return val ? "true" : "false"; }

inline Wstring ToWString(int val) { return _Integral_to_string<wchar_t>(val); }
inline Wstring ToWString(unsigned int val) { return _Integral_to_string<wchar_t>(val); }
inline Wstring ToWString(long val) { return _Integral_to_string<wchar_t>(val); }
inline Wstring ToWString(unsigned long val) { return _Integral_to_string<wchar_t>(val); }
inline Wstring ToWString(long long val) { return _Integral_to_string<wchar_t>(val); }
inline Wstring ToWString(unsigned long long val) { return _Integral_to_string<wchar_t>(val); }


SPACE_END

namespace std
{
    template<class T>
    using STRING = Core::STRING<T>;

    template<class TChar, class String>
    struct std::hash<Core::CustomString<TChar, String>> {
        size_t operator()(const Core::CustomString<TChar, String>& str) const {
            return std::hash<STRING<TChar>>{}(str.c_str());
        }
    };
    template<class TChar, class String>
    struct std::equal_to<Core::CustomString<TChar, String>> {
        bool operator()(const Core::CustomString<TChar, String>& lhs, const Core::CustomString<TChar, String>& rhs) const {
            return lhs == rhs;
        }
    };

    template<class TChar, class String>
    struct std::less<Core::CustomString<TChar, String>> {
        bool operator()(const Core::CustomString<TChar, String>& lhs, const Core::CustomString<TChar, String>& rhs) const {
            return lhs < rhs;
        }
    };

    template<>
    struct formatter<Core::String, char> : formatter<string_view, char> {
        auto format(const Core::String& str, format_context& ctx) const {
            return formatter<string_view, char>::format(string_view(str.data(), str.size()), ctx);
        }
    };

    template<>
    struct formatter<Core::Wstring, wchar_t> : formatter<wstring_view, wchar_t> {
        auto format(const Core::Wstring& str, wformat_context& ctx) const {
            return formatter<wstring_view, wchar_t>::format(wstring_view(str.data(), str.size()), ctx);
        }
    };
}

