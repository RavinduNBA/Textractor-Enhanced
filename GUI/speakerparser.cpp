#include "speakerparser.h"
#include "common.h"

namespace
{
	std::wstring TrimWhitespace(std::wstring text)
	{
		auto first = text.find_first_not_of(L" \t");
		if (first == std::wstring::npos) return {};
		auto last = text.find_last_not_of(L" \t");
		return text.substr(first, last - first + 1);
	}

	bool LooksLikeSpeaker(const std::wstring& speaker)
	{
		if (speaker.empty() || speaker.size() > 32) return false;
		if (speaker.find_first_of(L"\r\n:：。！？,.;!?/\\") != std::wstring::npos) return false;
		return true;
	}
}

std::optional<SpeakerLine> ParseSpeakerLine(const std::wstring& sentence)
{
	auto contentStart = sentence.find_first_not_of(L" \t");
	if (contentStart == std::wstring::npos) return {};

	for (auto opening : { L'「', L'『' })
		if (auto separator = sentence.find(opening, contentStart); separator != std::wstring::npos)
		{
			if (sentence.substr(contentStart, separator - contentStart).find_first_of(L"\r\n") != std::wstring::npos) continue;
			auto speaker = TrimWhitespace(sentence.substr(contentStart, separator - contentStart));
			if (LooksLikeSpeaker(speaker)) return SpeakerLine{ std::move(speaker), separator };
		}

	if (auto separator = sentence.find_first_of(L":：", contentStart); separator != std::wstring::npos)
	{
		if (sentence.substr(contentStart, separator - contentStart).find_first_of(L"\r\n") != std::wstring::npos) return {};
		if (sentence.substr(separator + 1, 2) == L"//") return {};
		auto speaker = TrimWhitespace(sentence.substr(contentStart, separator - contentStart));
		if (LooksLikeSpeaker(speaker))
		{
			auto prefixEnd = separator + 1;
			while (prefixEnd < sentence.size() && (sentence[prefixEnd] == L' ' || sentence[prefixEnd] == L'\t')) ++prefixEnd;
			return SpeakerLine{ std::move(speaker), prefixEnd };
		}
	}
	return {};
}

std::wstring FormatSpeakerDisplay(std::wstring sentence)
{
	if (auto speakerLine = ParseSpeakerLine(sentence))
	{
		auto contentStart = sentence.find_first_not_of(L" \t");
		sentence.replace(contentStart, speakerLine->prefixEnd - contentStart, speakerLine->speaker + L":\n");
	}
	return sentence;
}

TEST(
	{
		assert(ParseSpeakerLine(L"Alice「Hello」")->speaker == L"Alice");
		assert(ParseSpeakerLine(L"Alice：Hello")->speaker == L"Alice");
		assert(ParseSpeakerLine(L"Alice: Hello")->prefixEnd == 7);
		assert(!ParseSpeakerLine(L"これは普通の文章です"));
		assert(!ParseSpeakerLine(L"https://example.com"));
		assert(FormatSpeakerDisplay(L"Alice「Hello」") == L"Alice:\n「Hello」");
	}
);
