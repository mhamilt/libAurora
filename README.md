# libAurora

![ ](img/logos/aurora_logo_inv.png#gh-dark-mode-only)

![ ](img/logos/ap_logo_inv.png#gh-dark-mode-only)![ ](img/logos/conv_logo_inv.png#gh-dark-mode-only)![ ](img/logos/kirk_logo_inv.png#gh-dark-mode-only)![ ](img/logos/ssg_logo_inv.png#gh-dark-mode-only)![ ](img/logos/sti_logo_inv.png#gh-dark-mode-only)![ ](img/logos/tha_logo_inv.png#gh-dark-mode-only)![ ](img/logos/xfn_logo_inv.png#gh-dark-mode-only)


![ ](img/logos/aurora_logo.png#gh-light-mode-only)

![ ](img/logos/ap_logo.png#gh-light-mode-only)![ ](img/logos/conv_logo.png#gh-light-mode-only)![ ](img/logos/kirk_logo.png#gh-light-mode-only)![ ](img/logos/ssg_logo.png#gh-light-mode-only)![ ](img/logos/sti_logo.png#gh-light-mode-only)![ ](img/logos/tha_logo.png#gh-light-mode-only)![ ](img/logos/xfn_logo.png#gh-light-mode-only)

## About 

libAurora is a software heritage project to transform Angelo Farina's Aurora Plug-ins into a reusable, cross-platform modern C++ library. Basis of the code is Simone Campanini's [Aurora for Audacity implementation](https://github.com/Aurora-for-Audacity/Aurora-for-Audacity)
The current goal of the project is the reimplementation of Aurora into the Audacity DAW. 

The first step to is the removal of the Audacity and [WxWidgets](https://github.com/wxWidgets/wxWidgets) code that leaked into the Aurora source code.


## Structure

Aurora source code is in `src/`. Not all original source has been transferred, the original still resides in [Aurora for Audacity](https://github.com/Aurora-for-Audacity/Aurora-for-Audacity).

`AuroraTests` contains a simple programme which is being used a document for minimal working examples.


`external` contains dependencies, which is currently just [kissfft](https://github.com/mborgerding/kissfft)


## Plug-in

Original Aurora Source was based around a suite of 7 plug-ins, which are will be translated into 7 class units.

- Acoustical Parameters
- Convolver
- Kirkeby Filter Inversion
- SineSweepGenerator
- Speech Transmission Index
- TimeHistoryAnalyzer
- XFunctions (Cross Functions)

### Unit Status

Listed below is the status of each unit, whether all of its source is present, compiling and has a minimal working library example.

| Unit                      | Present | Building | Working Example |
| ------------------------- | :-----: | :------: | :-------------: |
| Acoustical Parameters     |   ✅    |    ✅    |       ✅        |
| Convolver                 |   ✅    |    ✅    |       ✅        |
| Kirkeby Filter Inversion  |   ❌    |    ❌    |       ❌        |
| SineSweepGenerator        |   ✅    |    ✅    |       ✅        |
| Speech Transmission Index |   ❌    |    ❌    |       ❌        |
| TimeHistoryAnalyzer       |   ❌    |    ❌    |       ❌        |
| XFunctions                |   ❌    |    ❌    |       ❌        |
