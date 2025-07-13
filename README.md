# 🔍 System Gatherer - Educational Malware Sample

**Part of the [Malware Analysis Learning Course](https://github.com/msh31/malware-analysis) - Challenge 1A**

Educational demonstration of Windows system enumeration techniques commonly used by malware for initial reconnaissance.

## ⚠️ Educational Purpose Only

This code demonstrates system enumeration techniques for cybersecurity education in controlled environments.

## 🎯 Learning Objectives

This project teaches fundamental malware reconnaissance techniques:

### **System Intelligence Gathering**
- **Registry-based OS detection** that bypasses Windows compatibility shims
- **Hardware enumeration** for system profiling
- **Architecture detection** for payload selection
- **Understanding why malware avoids official APIs**

### **Technical Skills Demonstrated**
- Direct Windows Registry access via Win32 API
- System information gathering through `GetSystemInfo()`
- String handling and data formatting in C++

## 🔧 Techniques Implemented

### **Registry Access Pattern**

### **APIs Utilized**
- `RegOpenKeyExA()` - Registry key access
- `RegQueryValueExA()` - Value retrieval
- `GetSystemInfo()` - Hardware information
- Standard C++ I/O for output formatting

### **Why These Techniques?**
Real malware uses these exact methods because:
- **GetVersionEx() lies** on modern Windows versions
- **Registry access is reliable** across all Windows versions
- **Direct system calls** are harder to hook/monitor
- **Minimal API footprint** reduces detection signatures

## 🛠️ Compilation & Usage

### **Requirements**
- **Platform:** Windows 10/11
- **Compiler:** Visual Studio 2022 or MinGW-w64

### **Build Instructions**

**Visual Studio 2022:**
```bash
start system-gatherer.sln

# Build in Release mode for analysis
Build → Configuration Manager → Release → Build Solution
```

**Command Line (MinGW):**
```bash
g++ -o system-gatherer.exe src/main.cpp -ladvapi32 -static
```

### **Safe Execution**
```bash
# Run in isolated VM only
./system-gatherer.exe

# Output saved to system_info.txt
```

## 📊 Sample Output

```
=== SYSTEM ENUMERATION ===
OS: Windows 10 Pro
Build: 19045
Release: 2009
Processors: 4
Architecture: x64
```

## 📖 References & Further Reading

- **[Practical Malware Analysis](https://nostarch.com/malware)** - Chapter 3: Dynamic Analysis
- **[MITRE ATT&CK: System Information Discovery](https://attack.mitre.org/techniques/T1082/)**
- **[Windows Registry Reference](https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry)**
- **[Malware Analysis Bootcamp](https://class.malware.re/)** - System Enumeration Module

## 📊 Analysis Reports (To-Do)

See [ANALYSIS.md](./ANALYSIS.md) for detailed:
- Static analysis with PE-bear and hex editors
- Dynamic analysis with Process Monitor and debuggers
- Network analysis with Wireshark (baseline establishment)
- Professional malware analysis reporting format

---

**🎓 Educational Note:** This project demonstrates legitimate cybersecurity research methodology. Understanding attack techniques is essential for building effective defenses and developing security solutions.