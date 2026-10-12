# Vocal Harmonizer

An audio plugin (VST3) that creates vocal harmonies from a lead vocal, with no MIDI needed: pick a key and scale, then configure the harmony voices.

**Status:** starter version. It loads in your DAW and passes the vocal through with an output gain knob. Harmony voices come next.

Targets Windows and Linux, tested against Studio One.

## Installing a build

1. Open the latest run under **Actions → Build** on GitHub and download `VocalHarmonizer-Windows-VST3` or `VocalHarmonizer-Linux-VST3`.
2. Unzip it. You get a folder called `Vocal Harmonizer.vst3`.
3. Copy that whole folder to:
   - Windows: `C:\Program Files\Common Files\VST3\`
   - Linux: `~/.vst3/`
4. In Studio One, rescan plugins (Options → Locations → VST Plug-Ins → Reset Blocklist / Rescan) and look for **Vocal Harmonizer** under Effects.

## Building it yourself

Needs CMake 3.22+ and a C++20 compiler (Visual Studio 2022 on Windows). JUCE is downloaded automatically.

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

On Linux, install the packages listed in `.github/workflows/build.yml` first.
