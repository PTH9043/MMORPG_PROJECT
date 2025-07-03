#pragma once 


template<typename T, class ...Args>
concept ConstructArgsCheck = std::is_constructible_v<T, Args...>;

template <typename T, typename... Args>
concept CheckToSameMethodArgs = requires(T * t, Args&&... args) {
	{ t->NativeConstruct(args...) } -> std::same_as<EErrorState>;
};

template<class T>
concept CheckStdStrings = std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring>;

template<class T>
concept CheckChar = std::is_same_v<T, char> || std::is_same_v<T, wchar_t>;

template<class TChar, class TString>
concept CheckCustomString = CheckStdStrings<TString> || CheckChar<TChar>;