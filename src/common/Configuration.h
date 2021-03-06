#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>
#include <QFont>
#include <Cutter.h>

#define Config() (Configuration::instance())
#define ConfigColor(x) Config()->getColor(x)

enum ColorFlags {
    LightFlag = 1,
    DarkFlag = 2
};

struct CutterQtTheme {
    QString name;
    ColorFlags flag;
};

extern const QList<CutterQtTheme> kCutterQtThemesList;

class Configuration : public QObject
{
    Q_OBJECT
private:
    QSettings s;
    static Configuration *mPtr;

    void loadInitial();

    // Colors
    void loadBaseDark();
    void loadDefaultTheme();
    void loadDarkTheme();
    void setColor(const QString &name, const QColor &color);

    // Images
    QString logoFile;

    // Asm Options
    void applySavedAsmOptions();

public:
    // Functions
    Configuration();
    static Configuration *instance();

    void resetAll();

    // Languages
    QLocale getCurrLocale() const;
    void setLocale(const QLocale &l);

    // Fonts
    const QFont getFont() const;
    void setFont(const QFont &font);

    // Colors
    void setLastThemeOf(const CutterQtTheme &currQtTheme, const QString& theme);
    QString getLastThemeOf(const CutterQtTheme &currQtTheme) const;
    const QColor getColor(const QString &name) const;
    void setTheme(int theme);
    int getTheme()
    {
        return s.value("ColorPalette", 0).toInt();
    }

    QString getDirProjects();
    void setDirProjects(const QString &dir);

    void setNewFileLastClicked(int lastClicked);
    int getNewFileLastClicked();

    // Images
    QString getLogoFile();

    // Asm Options
    void resetToDefaultAsmOptions();

    // Graph
    int getGraphBlockMaxChars() const
    {
        return s.value("graph.maxcols", 100).toInt();
    }
    void setGraphBlockMaxChars(int ch)
    {
        s.setValue("graph.maxcols", ch);
    }

    QString getColorTheme() const     { return s.value("theme", "cutter").toString(); }
    void setColorTheme(const QString &theme);

    /*!
     * \brief Get the value of a config var either from r2 or settings, depending on the key.
     */
    QVariant getConfigVar(const QString &key);
    bool getConfigBool(const QString &key);
    int getConfigInt(const QString &key);
    QString getConfigString(const QString &key);

    /*!
     * \brief Set the value of a config var either to r2 or settings, depending on the key.
     */
    void setConfig(const QString &key, const QVariant &value);

signals:
    void fontsUpdated();
    void colorsUpdated();
};

#endif // CONFIGURATION_H
