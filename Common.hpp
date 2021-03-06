#pragma once

#include <QString>
#include <QMetaType>
#include "zeus/Math.hpp"

enum class Platform { Invalid, MacOS, Win32, Linux, MAXPlatform };
QString PlatformToString(Platform plat);
Platform StringToPlatform(const QString& str);

#if __APPLE__
constexpr Platform CurPlatform = Platform::MacOS;
#elif _WIN32
constexpr Platform CurPlatform = Platform::Win32;
#elif __linux__
constexpr Platform CurPlatform = Platform::Linux;
#endif

extern const QString CurPlatformString;

enum class Architecture { Invalid, X86, X86_64, ARM, ARM64, MAXArchitecture };
QString ArchitectureToString(Architecture arch);
Architecture StringToArchitecture(const QString& str);

extern Architecture CurArchitecture;
extern QString CurArchitectureString;

enum class VectorISA { Invalid, X87, SSE, SSE2, SSE3, SSE41, AVX, AVX2, AVX512, MAXVectorISA };
QString VectorISAToString(VectorISA visa);
VectorISA StringToVectorISA(const QString& str);

class URDEVersion {
  QString m_version{};
  Platform m_platform = CurPlatform;
  Architecture m_architecture = CurArchitecture;
  VectorISA m_vectorISA = VectorISA::Invalid;
  QString m_extension{};
  QString m_extra{};

public:
  URDEVersion() = default;
  explicit URDEVersion(const QString& filename);
  bool isValid() const { return !m_version.isEmpty(); }
  QString fileString(bool withExtension) const;
  QString getVersion() const { return m_version; }
  Platform getPlatform() const { return m_platform; }
  Architecture getArchitecture() const { return m_architecture; }
  VectorISA getVectorISA() const { return m_vectorISA; }
  QString getExtra() const { return m_extra; }
};
Q_DECLARE_METATYPE(URDEVersion);

void InitializePlatform();
