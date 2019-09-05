#pragma once

#include "Message.h"
#include "User.h"


class LoginRequestMessage : public Message
{
	friend MessageFactory;

private:

	QString m_username;

protected:

	LoginRequestMessage();		// empty constructor

	// Costruct LoginRequest message with the username of the account that is trying to login
	LoginRequestMessage(QString username);

public:

	~LoginRequestMessage() {};

	void readFrom(QDataStream& stream) override;
	void sendTo(QTcpSocket* socket) const override;

	QString getUsername() const;
};



class LoginChallengeMessage : public Message
{
	friend MessageFactory;

private:

	QByteArray m_salt;
	QByteArray m_nonce;

protected:

	LoginChallengeMessage();		// empty constructor

	// Costruct LoginChallenge message with the cryptographic nonce
	LoginChallengeMessage(QByteArray salt, QByteArray nonce);

public:

	~LoginChallengeMessage() {};

	void readFrom(QDataStream& stream) override;
	void sendTo(QTcpSocket* socket) const override;

	QByteArray getSalt() const;
	QByteArray getNonce() const;
};



class LoginUnlockMessage : public Message
{
	friend MessageFactory;

private:

	QByteArray m_token;

protected:

	LoginUnlockMessage();		// empty constructor

	// Costruct LoginUnlock message with the solved cryptographic challenge
	LoginUnlockMessage(QByteArray token);

public:

	~LoginUnlockMessage() {};

	void readFrom(QDataStream& stream) override;
	void sendTo(QTcpSocket* socket) const override;

	QByteArray getToken() const;
};



class LoginGrantedMessage : public Message
{
	friend MessageFactory;

private:

	User m_user;

protected:

	LoginGrantedMessage();		// empty constructor

	// Costruct LoginGranted message with the account information for the user
	LoginGrantedMessage(User loggedUser);

public:

	~LoginGrantedMessage() {};

	void readFrom(QDataStream& stream) override;
	void sendTo(QTcpSocket* socket) const override;

	User& getLoggedUser();
};



class LoginErrorMessage : public Message
{
	friend MessageFactory;

private:

	QString m_error;

protected:

	LoginErrorMessage();	 // empty constructor

	// Costruct LoginError message with a string as the error description
	LoginErrorMessage(QString reason);

public:

	~LoginErrorMessage() {};

	void readFrom(QDataStream& stream) override;
	void sendTo(QTcpSocket* socket) const override;

	QString getErrorMessage() const;
};
