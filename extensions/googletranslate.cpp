#include "qtcommon.h"
#include "translatewrapper.h"
#include "devtools.h"
#include "network.h"

extern const wchar_t* TRANSLATION_ERROR;

const char* TRANSLATION_PROVIDER = "Google Translate";
const char* GET_API_KEY_FROM = "https://console.cloud.google.com/marketplace/product/google/translate.googleapis.com";
extern const QStringList languagesTo
{
   "Afrikaans",
   "Albanian",
   "Amharic",
   "Arabic",
   "Armenian",
   "Azerbaijani",
   "Basque",
   "Belarusian",
   "Bengali",
   "Bosnian",
   "Bulgarian",
   "Catalan",
   "Cebuano",
   "Chichewa",
   "Chinese (Simplified)",
   "Chinese (Traditional)",
   "Corsican",
   "Croatian",
   "Czech",
   "Danish",
   "Dutch",
   "English",
   "Esperanto",
   "Estonian",
   "Filipino",
   "Finnish",
   "French",
   "Frisian",
   "Galician",
   "Georgian",
   "German",
   "Greek",
   "Gujarati",
   "Haitian Creole",
   "Hausa",
   "Hawaiian",
   "Hebrew",
   "Hindi",
   "Hmong",
   "Hungarian",
   "Icelandic",
   "Igbo",
   "Indonesian",
   "Irish",
   "Italian",
   "Japanese",
   "Javanese",
   "Kannada",
   "Kazakh",
   "Khmer",
   "Kinyarwanda",
   "Korean",
   "Kurdish (Kurmanji)",
   "Kyrgyz",
   "Lao",
   "Latin",
   "Latvian",
   "Lithuanian",
   "Luxembourgish",
   "Macedonian",
   "Malagasy",
   "Malay",
   "Malayalam",
   "Maltese",
   "Maori",
   "Marathi",
   "Mongolian",
   "Myanmar (Burmese)",
   "Nepali",
   "Norwegian",
   "Odia (Oriya)",
   "Pashto",
   "Persian",
   "Polish",
   "Portuguese",
   "Punjabi",
   "Romanian",
   "Russian",
   "Samoan",
   "Scots Gaelic",
   "Serbian",
   "Sesotho",
   "Shona",
   "Sindhi",
   "Sinhala",
   "Slovak",
   "Slovenian",
   "Somali",
   "Spanish",
   "Sundanese",
   "Swahili",
   "Swedish",
   "Tajik",
   "Tamil",
   "Tatar",
   "Telugu",
   "Thai",
   "Turkish",
   "Turkmen",
   "Ukrainian",
   "Urdu",
   "Uyghur",
   "Uzbek",
   "Vietnamese",
   "Welsh",
   "Xhosa",
   "Yiddish",
   "Yoruba",
   "Zulu",
}, languagesFrom = languagesTo;
extern const std::unordered_map<std::wstring, std::wstring> codes
{
	{ { L"Afrikaans" }, { L"af" } },
	{ { L"Albanian" }, { L"sq" } },
	{ { L"Amharic" }, { L"am" } },
	{ { L"Arabic" }, { L"ar" } },
	{ { L"Armenian" }, { L"hy" } },
	{ { L"Azerbaijani" }, { L"az" } },
	{ { L"Basque" }, { L"eu" } },
	{ { L"Belarusian" }, { L"be" } },
	{ { L"Bengali" }, { L"bn" } },
	{ { L"Bosnian" }, { L"bs" } },
	{ { L"Bulgarian" }, { L"bg" } },
	{ { L"Catalan" }, { L"ca" } },
	{ { L"Cebuano" }, { L"ceb" } },
	{ { L"Chichewa" }, { L"ny" } },
	{ { L"Chinese (Simplified)" }, { L"zh-CN" } },
	{ { L"Chinese (Traditional)" }, { L"zh-TW" } },
	{ { L"Corsican" }, { L"co" } },
	{ { L"Croatian" }, { L"hr" } },
	{ { L"Czech" }, { L"cs" } },
	{ { L"Danish" }, { L"da" } },
	{ { L"Dutch" }, { L"nl" } },
	{ { L"English" }, { L"en" } },
	{ { L"Esperanto" }, { L"eo" } },
	{ { L"Estonian" }, { L"et" } },
	{ { L"Filipino" }, { L"tl" } },
	{ { L"Finnish" }, { L"fi" } },
	{ { L"French" }, { L"fr" } },
	{ { L"Frisian" }, { L"fy" } },
	{ { L"Galician" }, { L"gl" } },
	{ { L"Georgian" }, { L"ka" } },
	{ { L"German" }, { L"de" } },
	{ { L"Greek" }, { L"el" } },
	{ { L"Gujarati" }, { L"gu" } },
	{ { L"Haitian Creole" }, { L"ht" } },
	{ { L"Hausa" }, { L"ha" } },
	{ { L"Hawaiian" }, { L"haw" } },
	{ { L"Hebrew" }, { L"iw" } },
	{ { L"Hindi" }, { L"hi" } },
	{ { L"Hmong" }, { L"hmn" } },
	{ { L"Hungarian" }, { L"hu" } },
	{ { L"Icelandic" }, { L"is" } },
	{ { L"Igbo" }, { L"ig" } },
	{ { L"Indonesian" }, { L"id" } },
	{ { L"Irish" }, { L"ga" } },
	{ { L"Italian" }, { L"it" } },
	{ { L"Japanese" }, { L"ja" } },
	{ { L"Javanese" }, { L"jw" } },
	{ { L"Kannada" }, { L"kn" } },
	{ { L"Kazakh" }, { L"kk" } },
	{ { L"Khmer" }, { L"km" } },
	{ { L"Kinyarwanda" }, { L"rw" } },
	{ { L"Korean" }, { L"ko" } },
	{ { L"Kurdish (Kurmanji)" }, { L"ku" } },
	{ { L"Kyrgyz" }, { L"ky" } },
	{ { L"Lao" }, { L"lo" } },
	{ { L"Latin" }, { L"la" } },
	{ { L"Latvian" }, { L"lv" } },
	{ { L"Lithuanian" }, { L"lt" } },
	{ { L"Luxembourgish" }, { L"lb" } },
	{ { L"Macedonian" }, { L"mk" } },
	{ { L"Malagasy" }, { L"mg" } },
	{ { L"Malay" }, { L"ms" } },
	{ { L"Malayalam" }, { L"ml" } },
	{ { L"Maltese" }, { L"mt" } },
	{ { L"Maori" }, { L"mi" } },
	{ { L"Marathi" }, { L"mr" } },
	{ { L"Mongolian" }, { L"mn" } },
	{ { L"Myanmar (Burmese)" }, { L"my" } },
	{ { L"Nepali" }, { L"ne" } },
	{ { L"Norwegian" }, { L"no" } },
	{ { L"Odia (Oriya)" }, { L"or" } },
	{ { L"Pashto" }, { L"ps" } },
	{ { L"Persian" }, { L"fa" } },
	{ { L"Polish" }, { L"pl" } },
	{ { L"Portuguese" }, { L"pt" } },
	{ { L"Punjabi" }, { L"pa" } },
	{ { L"Romanian" }, { L"ro" } },
	{ { L"Russian" }, { L"ru" } },
	{ { L"Samoan" }, { L"sm" } },
	{ { L"Scots Gaelic" }, { L"gd" } },
	{ { L"Serbian" }, { L"sr" } },
	{ { L"Sesotho" }, { L"st" } },
	{ { L"Shona" }, { L"sn" } },
	{ { L"Sindhi" }, { L"sd" } },
	{ { L"Sinhala" }, { L"si" } },
	{ { L"Slovak" }, { L"sk" } },
	{ { L"Slovenian" }, { L"sl" } },
	{ { L"Somali" }, { L"so" } },
	{ { L"Spanish" }, { L"es" } },
	{ { L"Sundanese" }, { L"su" } },
	{ { L"Swahili" }, { L"sw" } },
	{ { L"Swedish" }, { L"sv" } },
	{ { L"Tajik" }, { L"tg" } },
	{ { L"Tamil" }, { L"ta" } },
	{ { L"Tatar" }, { L"tt" } },
	{ { L"Telugu" }, { L"te" } },
	{ { L"Thai" }, { L"th" } },
	{ { L"Turkish" }, { L"tr" } },
	{ { L"Turkmen" }, { L"tk" } },
	{ { L"Ukrainian" }, { L"uk" } },
	{ { L"Urdu" }, { L"ur" } },
	{ { L"Uyghur" }, { L"ug" } },
	{ { L"Uzbek" }, { L"uz" } },
	{ { L"Vietnamese" }, { L"vi" } },
	{ { L"Welsh" }, { L"cy" } },
	{ { L"Xhosa" }, { L"xh" } },
	{ { L"Yiddish" }, { L"yi" } },
	{ { L"Yoruba" }, { L"yo" } },
	{ { L"Zulu" }, { L"zu" } },
	{ { L"?" }, { L"auto" } }
};

bool translateSelectedOnly = true, useRateLimiter = true, rateLimitSelected = false, useCache = true, useFilter = true;
int tokenCount = 30, rateLimitTimespan = 60000, maxSentenceSize = 1000;

BOOL WINAPI DllMain(HMODULE, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DevTools::Initialize();
		DevTools::StartChrome();
	}
	else if (reason == DLL_PROCESS_DETACH) DevTools::Close();
	return TRUE;
}

std::pair<bool, std::wstring> Translate(const std::wstring& text, TranslationParam tlp)
{
	if (!tlp.authKey.empty())
	{
		std::wstring translateFromComponent = tlp.translateFrom == L"?" ? L"" : L"&source=" + codes.at(tlp.translateFrom);
		if (HttpRequest httpRequest{
			L"Mozilla/5.0 Textractor",
			L"translation.googleapis.com",
			L"POST",
			FormatString(L"/language/translate/v2?format=text&target=%s&key=%s%s", codes.at(tlp.translateTo), tlp.authKey, translateFromComponent).c_str(),
			FormatString(R"({"q":["%s"]})", JSON::Escape(WideStringToString(text)))
		})
			if (auto translation = Copy(JSON::Parse(httpRequest.response)[L"data"][L"translations"][0][L"translatedText"].String())) return { true, translation.value() };
			else return { false, FormatString(L"%s: %s", TRANSLATION_ERROR, httpRequest.response) };
		else return { false, FormatString(L"%s (code=%u)", TRANSLATION_ERROR, httpRequest.errorCode) };
	}

	if (!DevTools::WaitForConnection(10000)) return { false, L"Google Translate browser is not connected." };
	static std::mutex translationMutex;
	std::scoped_lock lock(translationMutex);
	std::wstring translationUrl = FormatString(L"https://translate.google.com/?sl=%s&tl=%s&text=%s&op=translate", codes.at(tlp.translateFrom), codes.at(tlp.translateTo), Escape(text));
	DevTools::SendRequest("Page.navigate", FormatString(LR"({"url":"%s"})", translationUrl));
	for (int retry = 0; ++retry < 100; Sleep(100))
	{
		auto pageState = DevTools::SendRequest("Runtime.evaluate", LR"({"expression":"document.readyState","returnByValue":true})");
		if (Copy(pageState[L"result"][L"value"].String()) == L"complete") break;
	}
	static bool captchaPrompted = false;
	for (int retry = 0; ++retry < 200; Sleep(100))
	{
		auto result = DevTools::SendRequest("Runtime.evaluate", LR"JS({"expression":"document.querySelector('.result-container')?.textContent.trim() || document.querySelector('.ryNqvb')?.textContent.trim() || ''","returnByValue":true})JS");
		if (auto translation = Copy(result[L"result"][L"value"].String())) if (!translation->empty()) return { true, HTML::Unescape(translation.value()) };
		auto captcha = DevTools::SendRequest("Runtime.evaluate", LR"JS({"expression":"/captcha|unusual traffic|not a robot/i.test(document.body?.innerText || '')","returnByValue":true})JS");
		if (captcha[L"result"][L"value"].Boolean() && !captchaPrompted)
		{
			captchaPrompted = true;
			MessageBoxW(nullptr, L"Solve the Google CAPTCHA in the Chrome window controlled by Textractor. The same browser session will retry automatically.", L"Google Translate CAPTCHA", MB_OK | MB_ICONINFORMATION);
		}
	}
	return { false, L"Google Translate did not return a result." };
}
