#pragma once

#include <QTextBlockFormat>
#include <QTextListFormat>

class TextBlockID;
class TextBlock;


class TextBlockID
{
	/* Operators for QDataStream serialization and deserialization */
	friend QDataStream& operator>>(QDataStream& in, TextBlockID& bid);			// Input
	friend QDataStream& operator<<(QDataStream& out, const TextBlockID& bid);	// Output

private:

	qint32 _number;
	qint32 _authorId;

public:

	TextBlockID();				// Empty constructor for deserialization purposes

	TextBlockID(qint32 num, qint32 uid);		// Construct a TextBlockID with the specified pair of values
	TextBlockID(const TextBlock& block);		// Copy the TextBlockID of the reference block
	TextBlockID(std::nullptr_t);				// Construct a null TextBlockID

	qint32 getBlockNumber() const;
	qint32 getAuthorId() const;

	// Comparators to use this type as a key in QMap collections, or store in a QList
	bool operator<(const TextBlockID& other) const noexcept;		
	bool operator>(const TextBlockID& other) const noexcept;
	bool operator==(const TextBlockID& other) const noexcept;
	operator bool() const noexcept;
};

Q_DECLARE_METATYPE(TextBlockID);


class TextBlock
{
	/* Operators for QDataStream serialization and deserialization */
	friend QDataStream& operator>>(QDataStream& in, TextBlock& sym);			// Input
	friend QDataStream& operator<<(QDataStream& out, const TextBlock& sym);		// Output

private:

	TextBlockID _blockId;
	QTextBlockFormat _blockFormat;
	QTextListFormat _listFormat;
	QVector<qint32> _fPosBegin;
	QVector<qint32> _fPosEnd;

public:

	TextBlock();		// Empty constructor, to use before populating fields with deserialization

	TextBlock(qint32 blockNum, qint32 authorId, QTextBlockFormat fmt);
	TextBlock(TextBlockID blockId, QTextBlockFormat fmt);
	TextBlock(TextBlockID blockId, QTextBlockFormat blockFmt, QTextListFormat listFmt);

	/* setters */
	void setFormat(QTextBlockFormat fmt);
	void setBegin(QVector<qint32> fPosBegin);
	void setEnd(QVector<qint32> fPosEnd);
	void setListFormat(QTextListFormat fmt);

	/* getters */
	TextBlockID getId() const;
	QTextBlockFormat getFormat() const;
	QVector<qint32> begin() const;
	QVector<qint32> end() const;
	QTextListFormat getListFormat() const;
	bool isEmpty() const;

};

Q_DECLARE_METATYPE(TextBlock);