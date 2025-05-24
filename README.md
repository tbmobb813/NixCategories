# NixCategories (Fork of Game Categories Lite)

**NixCategories** is a modern fork of the popular Game Categories Lite PSP plugin.  
It improves how games and homebrew apps are organized on the XMB by supporting:

- ✅ Folder-based categorization
- ✅ Filename prefix parsing (e.g. `[Action] Game Name`)
- ✅ New: `.ini`-based virtual category mapping
- ✅ Optional hybrid mode: combine all methods
- ✅ Future plans for favorites, smart sorting, and visual tags

---
📌 Roadmap INI-based virtual categories

Favorite tagging system

Sort by last played / size / region

Category icon support

Companion config tool (PC or Web)


🙏 Credits
Originally developed by Bubbletune and Codestation
Modernized and extended by @yourgithubname for NixLevel

Licensed under the GNU GPL v3


## 🔧 Installation

1. Copy `NixCategories.prx` to `seplugins/`
2. Add to `vsh.txt`:
3. Restart your PSP and hold **R** to access Recovery Mode if needed.

---

## ⚙️ Config File (`gclite.bin` or `.ini`)

This plugin reads categories from either:
- The folder structure under `ms0:/PSP/GAME/`
- Game name prefixes like `[RPG] Final Fantasy`
- A new `.ini` mapping file stored at `seplugins/categories.ini`

Example `.ini`:
```ini
[Action]
ULUS10567 = God of War
NPUH10027 = Tekken 6

[RPG]
ULES00177 = Final Fantasy Tactics

