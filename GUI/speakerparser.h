#pragma once

#include <string>
#include <optional>

struct SpeakerLine
{
	std::wstring speaker;
	size_t prefixEnd;
};

std::optional<SpeakerLine> ParseSpeakerLine(const std::wstring& sentence);
std::wstring FormatSpeakerDisplay(std::wstring sentence);
