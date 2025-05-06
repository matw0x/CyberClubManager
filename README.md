# Cyber Club Manager

## Structure

```
.
├── .clang-format
├── CMakeLists.txt
├── .gitignore
├── README.md
├── src
│   ├── main.cpp
│   ├── manager
│   │   ├── manager.cpp
│   │   └── manager.h
│   ├── parser
│   │   ├── parser.cpp
│   │   └── parser.h
│   ├── utils
│   │   ├── config.h
│   │   ├── event.h
│   │   ├── exception.h
│   │   ├── messages.h
│   │   ├── overseer
│   │   │   ├── overseer.cpp
│   │   │   └── overseer.h
│   │   ├── revenue.h
│   │   └── time
│   │       ├── time.cpp
│   │       └── time.h
│   └── validator
│       ├── validator.cpp
│       └── validator.h
└── tests
    ├── logic-directories
    ├── CMakeLists.txt
    └── run_tests.py
```

---

## Build and Run

#### Linux

```bash
git clone git@github.com:matw0x/CyberClubManager.git && cd CyberClubManager && mkdir build && cd build && cmake .. && cmake --build .
```

```bash
ctest # OPTIONAL
```

```bash
./ccm path_to_config.txt
```

---

#### Windows

```powershell
git clone git@github.com:matw0x/CyberClubManager.git; cd CyberClubManager; mkdir build; cd build; cmake ..; cmake --build . --config Release
```

```powershell
ctest # OPTIONAL
```

```powershell
ccm.exe path_to_config.txt
```

---
