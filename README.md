# Textractor

![How it looks](screenshot.png)

[English](README.md) ● [Español](README_ES.md) ● [简体中文](README_SC.md) ● [Русский](README_RU.md) ● [한국어](README_KR.md) ● [ภาษาไทย](README_TH.md) ● [Français](README_FR.md) ● [Italiano](README_IT.md) ● [日本語](README_JP.md) ● [Bahasa Indonesia](README_ID.md) ● [Português](README_PT.md) ● [Deutsch](README_DE.md)

**Textractor Enhanced** (a.k.a. NextHooker) is an open-source x86/x64 video game text hooker for Windows 7+ (and Wine) based off of [ITHVNR](https://web.archive.org/web/20160202084144/http://www.hongfire.com/forum/showthread.php/438331-ITHVNR-ITH-with-the-VNR-engine). This fork adds browser-based Google Translate integration through a persistent Chrome/Edge DevTools session.<br>
Watch the [tutorial video](docs/TUTORIAL.md) for a quick rundown on using it.

## Download

Textractor Enhanced releases are available [here](https://github.com/RavinduNBA/Textractor-Enhanced/releases). Separate x86 and x64 ZIP packages are provided.<br>
Official stable releases of the original Textractor can be found [here](https://github.com/Artikash/Textractor/releases).<br>
The last release of ITHVNR can be found [here](https://drive.google.com/open?id=13aHF4uIXWn-3YML_k2YCDWhtGgn5-tnO).<br>
Experimental builds of Textractor (with debug info) from the latest source can be found [here](https://ci.appveyor.com/project/Artikash/textractor/history) in the 'Artifacts' section of each job.

## Features

- Highly extensible and customizable
- Auto hook many game engines (including some not supported by VNR!)
- Hook text using /H "hook" codes (most AGTH codes supported)
- Automatically search for possible hook codes
- Browser-based Google Translate using the full Google Translate website
- Google Translate Advanced mode support through a persistent Chrome/Edge session
- Manual Google CAPTCHA solving in the controlled browser session, without opening a new tab for every line
- Translate selected threads only by default

## Support

Let me know of any bugs, games that Textractor has trouble hooking, feature requests, or other suggestions by posting an issue.<br>
If you have trouble hooking a game, please show me a way to freely download it or gift it to me on [Steam](https://steamcommunity.com/profiles/76561198097566313/).

## Extensions

See my [Example Extension project](https://github.com/Artikash/ExampleExtension) to see how to build an extension.<br>
See the extensions folder for examples of what extensions can do. 

### Browser-Based Google Translate

The enhanced Google Translate extension uses a browser session controlled through the Chrome DevTools Protocol. This allows Google Translate's website features, including Advanced mode, to be used without an API key. If Google presents a CAPTCHA, solve it in the controlled browser session; later translation requests reuse that session instead of opening a new browser tab.

The browser can run hidden by default. Use the DevTools settings to toggle **Hide Chrome** and control whether the browser window is visible. The extension defaults to translating the selected thread only.

### Dialogue Thread Roles and Speaker Names

Google Translate can assign different roles to text threads from **Settings** while a thread is selected:

- **Speaker** for a thread that contains only a character name
- **Dialogue** for a thread that contains only dialogue
- **Speaker + dialogue** for text such as `未来「のーぞーむーちゃんっ」`
- **Automatic** to use the normal translation behavior

For speaker threads, add name mappings in the Google Translate extension settings under **Speaker names**, one per line:

```text
未来=Mirai
京香=Kyoka
```

Mapped names are used directly instead of being sent to Google Translate, preventing names such as `未来` from being translated as the common word `future`. Speaker + dialogue threads are split into separate speaker and dialogue queries, then displayed as:

```text
Mirai:
Nozomu-chan!
```

## Contributing

All contributions are appreciated! Please email me at akashmozumdar@gmail.com if you have any questions about the codebase.<br>
You should use the standard process of making a pull request (fork, branch, commit changes, make PR from your branch to my master).<br>
Contributing a translation is easy: [text.cpp](text.cpp) contains all of the text strings that you need to translate. Translations of this README or the tutorial video transcript are also welcome.

## Compiling
Before compiling Textractor, you need Qt version 5.13 and Visual Studio with CMake support.
Clone Textractor's source and initialize submodules with `git clone https://github.com/Artikash/Textractor.git` and `git submodule update --init`.
You should then be able to just open the source folder in Visual Studio and build.

For this fork, install both Qt 5.13 MSVC kits: **MSVC 2017 32-bit** for x86 builds and **MSVC 2017 64-bit** for x64 builds. Build the `x86-RelWithDebInfo` or `x64-RelWithDebInfo` configuration for release packages.

## Project Architecture

The host injects texthook into the target process and connects to it via 2 pipe files.
texthook waits for the pipe to be connected, then injects a few instructions into any text outputting functions (e.g. TextOut, GetGlyphOutline) that cause their input to be sent through the pipe.<br>
Additional information about hooks is exchanged via shared memory.<br>
The text that the host receives through the pipe is then processed a little before being dispatched back to the GUI.<br>
Finally, the GUI dispatches the text to extensions before displaying it.

## [Developers](docs/CREDITS.md)
