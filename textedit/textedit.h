#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <QMap>
#include <QPointer>
#include <QMap>
#include <User.h>
#include "Presence.h"
#include "ProfileEditWindow.h"

//Serve per incapsulare tutti i metodi delle classi
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QLabel;
class QToolButton;


class TextEdit : public QMainWindow
{
	Q_OBJECT

public:
	TextEdit(QWidget* parent = 0);
	
	void setUser(User* user); //User logged
	void accountUpdateSuccessful(); //Account updated

	
	bool load(const QString& f);




public slots:
	void userCursorPositionChanged(qint32 position, qint32 user);
	void fileNew(QString name);
	void newPresence(qint32 userId, QString username, QImage image);
	void removePresence(qint32 userId);
	void accountUpdateFailed(QString error);


signals:
	void closeDocument();
	void newCursorPosition(qint32 position);
	void accountUpdate(QString name, QImage image);
	

private slots:
	void fileOpen();
	void filePrint();
	void filePrintPreview();
	void filePrintPdf();

	void fileShare();
	
	void editProfile();

	void highlightUsersText();
	void contentsChange(int position, int charsRemoved, int charsAdded);

	void textBold();
	void textUnderline();
	void textItalic();
	void textFamily(const QString& f);
	void textSize(const QString& p);
	void listStyle(int styleIndex);
	void textStyle(int styleIndex);
	void textColor();
	void textAlign(QAction* a);

	void currentCharFormatChanged(const QTextCharFormat& format);
	void cursorPositionChanged();

	void clipboardDataChanged();
	void printPreview(QPrinter*);


private:
	void setupFileActions();
	void setupEditActions();
	void setupTextActions();
	void setupShareActions();
	void setupUserActions();
	void setupOnlineUsersActions();
	void setCurrentFileName(const QString& fileName);

	void mergeFormatOnWordOrSelection(const QTextCharFormat& format);
	void fontChanged(const QFont& f);
	void colorChanged(const QColor& c);
	void alignmentChanged(Qt::Alignment a);

	//Extra selections and multiple cursors
	void handleUsersCursors();
	void handleMultipleSelections();
	void handleUserSelection(Presence p);

	//List type
	QToolButton* listButton;
	enum listType { standard, disc, circle, square, decimal, alpha, alphaupper, roman, romanupper };

	QMap<qint32, Presence> onlineUsers;
	//Logged user
	User* _user;

	//Edit window
	ProfileEditWindow* ew;

	QAction* actionTextBold;
	QAction* actionTextUnderline;
	QAction* actionTextItalic;
	QAction* actionTextColor;
	QAction* actionAlignLeft;
	QAction* actionAlignCenter;
	QAction* actionAlignRight;
	QAction* actionAlignJustify;
	QAction* actionUndo;
	QAction* actionRedo;
	QAction* actionShare;
	QAction* actionUser;
	QAction* actionHighlightUsers;
	QAction* actioncloseDocument;

#ifndef QT_NO_CLIPBOARD
	QAction* actionCut;
	QAction* actionCopy;
	QAction* actionPaste;
#endif

	QComboBox* comboStyle;
	QFontComboBox* comboFont;
	QComboBox* comboSize;

	QToolBar* tb;
	QString fileName;
	QTextEdit* textEdit;


};

#endif // TEXTEDIT_H