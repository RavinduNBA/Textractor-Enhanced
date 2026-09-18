# Textractor Enhanced

![How it looks](screenshot.png)

[English](README.md) | [Español](README_ES.md) | [简体中文](README_SC.md) | [Русский](README_RU.md) | [한국어](README_KR.md) | [ภาษาไทย](README_TH.md) | [Français](README_FR.md) | [Italiano](README_IT.md) | [日本語](README_JP.md) | [Bahasa Indonesia](README_ID.md) | [Português](README_PT.md) | [Deutsch](README_DE.md)

Textractor Enhanced is an open-source x86/x64 video-game text hooker for Windows 7+ and Wine. It supports automatic hook discovery, AGTH-compatible hook codes, extensible text processing, and translation workflows for visual novels and other games.

See the [tutorial](docs/TUTORIAL.md) for a quick introduction.

## Downloads

Release packages are available on the [Textractor Enhanced releases page](https://github.com/RavinduNBA/Textractor-Enhanced/releases).

Separate x86 and x64 ZIP packages are provided. Choose the package matching the architecture of the target game.

## Features

- Extensible and customizable text processing
- Automatic hook support for many game engines
- `/H` hook codes with support for most AGTH-style codes
- Automatic search for possible hook codes
- Browser-based Google Translate through a persistent Chrome or Edge DevTools session
- Google Translate website Advanced mode support
- Manual CAPTCHA solving in the controlled browser session
- Hidden browser mode with an option to show the browser window
- Translation of selected threads only
- Manual speaker, dialogue, and speaker-plus-dialogue thread roles
- Persistent speaker-name mappings such as `未来=Mirai`

## Google Translate

The Google Translate extension uses the Chrome DevTools Protocol instead of a separate HTTP session. This allows CAPTCHA cookies and website state to remain in the same controlled browser session.

The browser can run hidden by default. Open the DevTools settings to toggle **Hide Chrome** and control browser visibility. If Google presents a CAPTCHA, solve it in the controlled browser session. Later requests reuse the same session instead of opening a new browser tab for every line.

An API key is optional when using the browser-based workflow.

## Dialogue Roles and Speaker Names

Select a text thread, open **Settings**, and assign one of these roles:

- **Speaker**: the thread contains only a character name
- **Dialogue**: the thread contains only dialogue
- **Speaker + dialogue**: the thread contains text such as `未来「のーぞーむーちゃんっ」`
- **Automatic**: use normal translation behavior

For speaker threads, open the Google Translate extension settings and add mappings under **Speaker names**, one per line:

```text
未来=Mirai
京香=Kyoka
```

Mapped names are used directly instead of being sent to Google Translate. This prevents a character named `未来` from being translated as the common word `future`.

Speaker-plus-dialogue threads are split into separate speaker and dialogue queries. The output can then be displayed as:

```text
Mirai:
Nozomu-chan!
```

## Extensions

The `extensions` directory contains built-in extensions and examples of text filters, translators, window tools, and processing utilities.

## Building

Requirements:

- Qt 5.13
- Visual Studio with CMake support
- Qt 5.13 MSVC 2017 32-bit kit for x86 builds
- Qt 5.13 MSVC 2017 64-bit kit for x64 builds

Clone the repository and initialize its submodules:

```powershell
git clone https://github.com/RavinduNBA/Textractor-Enhanced.git
cd Textractor-Enhanced
git submodule update --init
```

Open the source folder in Visual Studio and select the appropriate x86 or x64 CMake configuration. Use `RelWithDebInfo` for release builds.

## Support

Report bugs, hook compatibility issues, and feature requests through the [GitHub issue tracker](https://github.com/RavinduNBA/Textractor-Enhanced/issues). Include the game architecture, Textractor architecture, relevant hook details, and reproducible steps when possible.

## Project Architecture

The host injects `texthook` into the target process and communicates with it through named pipes. `texthook` injects instructions into text-producing functions and sends captured text back to the host. Additional hook information is exchanged through shared memory.

The host processes captured text and dispatches completed sentences to the GUI and loaded extensions. Extensions can filter, transform, translate, or display the text before it is appended to the selected thread output.

## Credits

See [docs/CREDITS.md](docs/CREDITS.md) for project and dependency credits.
