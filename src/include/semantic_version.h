#pragma once

// Semantic version - see http://semver.org/

#include <string>
#include <ostream>

namespace semver
{
  namespace v1
  {

    class Version
    {
    public:
      Version(
          unsigned int major = 0,
          unsigned int minor = 0,
          unsigned int patch = 1,
          const std::string& prerelease = std::string{},
          const std::string& build = std::string{});

      // parse from a version string
      explicit Version(const std::string& s);

      unsigned int GetMajorVersion() const { return m_majorVersion; }
      unsigned int GetMinorVersion() const { return m_minorVersion; }
      unsigned int GetPatchVersion() const { return m_patchVersion; }

      // Create a new version by incrementing a part of a version. Other parts
      // will be reset to 0.
      Version NextMajorVersion() const;
      Version NextMinorVersion() const;
      Version NextPatchVersion() const;

      // A version satisfies another version if it is greater than or equal to
      // it in precedence. Additionally, pre-release versions and build versions
      // both satisfy their corresponding normal versions, and all pre-release
      // or build versions thereof.
      bool Satisfies(const Version& other) const;

      // Precedence is calculated by comparing the major, minor, patch,
      // pre-release and build parts in that order. Pre-release and build
      // strings are considered as lists of dot-separated identifiers, whereby
      // if an identifier is numeric, it is compared as such; otherwise
      // comparison is based on ASCII sort order.
      friend bool operator<(const Version& a, const Version& b);
      friend bool operator==(const Version& a, const Version& b);

      // A version is output as X.Y.Z (Major.Minor.Patch)
      // A pre-release string (eg alpha.1) may follow immediately, joined by a -
      // A build string may follow (eg 123.f83eaa931), joined by a +
      friend std::ostream& operator<<(std::ostream& s, const Version& v);

    private:
      unsigned int m_majorVersion = 0;
      unsigned int m_minorVersion = 0;
      unsigned int m_patchVersion = 1;
      std::string m_prereleaseVersion;
      std::string m_buildVersion;
    };

    inline bool operator!=(const Version& a, const Version& b)
    {
      return !(a == b);
    }

    inline bool operator>=(const Version& a, const Version& b)
    {
      return !(a < b);
    }

    inline bool operator<=(const Version& a, const Version& b)
    {
      return (a == b) || (a < b);
    }

    inline bool operator>(const Version& a, const Version& b)
    {
      return (a != b) && (a >= b);
    }
  }

  inline namespace v2
  {

    class Version
    {
    public:
      Version(
          unsigned int major = 0,
          unsigned int minor = 0,
          unsigned int patch = 1,
          const std::string& prerelease = std::string{},
          const std::string& build = std::string{});

      // parse from a version string
      explicit Version(const std::string& s);

      unsigned int GetMajorVersion() const { return m_majorVersion; }
      unsigned int GetMinorVersion() const { return m_minorVersion; }
      unsigned int GetPatchVersion() const { return m_patchVersion; }

      // Create a new version by incrementing a part of a version. Other parts
      // will be reset to 0.
      Version NextMajorVersion() const;
      Version NextMinorVersion() const;
      Version NextPatchVersion() const;

      // A version satisfies another version if it is greater than or equal to
      // it in precedence. Additionally, pre-release versions and build versions
      // both satisfy their corresponding normal versions, and all pre-release
      // or build versions thereof.
      bool Satisfies(const Version& other) const;

      // Precedence is calculated by comparing the major, minor, patch, and
      // pre-release parts in that order. Pre-release strings are considered as
      // lists of dot-separated identifiers, whereby if an identifier is
      // numeric, it is compared as such; otherwise comparison is based on ASCII
      // sort order. Note: according to semver v2.0.0, build version is NOT
      // considered when determining precedence.
      friend bool operator<(const Version& a, const Version& b);
      friend bool operator==(const Version& a, const Version& b);

      // For exact equality (as opposed to precedence equality)
      bool Equals(const Version& other) const;

      // A version is output as X.Y.Z (Major.Minor.Patch)
      // A pre-release string (eg alpha.1) may follow immediately, joined by a -
      // A build string may follow (eg 123.f83eaa931), joined by a +
      friend std::ostream& operator<<(std::ostream& s, const Version& v);

    private:
      unsigned int m_majorVersion = 0;
      unsigned int m_minorVersion = 0;
      unsigned int m_patchVersion = 1;
      std::string m_prereleaseVersion;
      std::string m_buildVersion;
    };

    inline bool operator!=(const Version& a, const Version& b)
    {
      return !(a == b);
    }

    inline bool operator>=(const Version& a, const Version& b)
    {
      return !(a < b);
    }

    inline bool operator<=(const Version& a, const Version& b)
    {
      return (a == b) || (a < b);
    }

    inline bool operator>(const Version& a, const Version& b)
    {
      return (a != b) && (a >= b);
    }
  }
}

