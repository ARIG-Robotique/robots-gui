#ifndef PROCESS_H
#define PROCESS_H

#include <QProcess>
#include <QVariant>

class Process : public QProcess
{
    Q_OBJECT
public:
    explicit Process( QObject* parent = Q_NULLPTR ) : QProcess( parent ) {}

    // If want to use Start with arguments
    Q_INVOKABLE void start( const QString& program, const QVariantList& arguments );

    // If wan to start without arguments for Qt > 5.14
    Q_INVOKABLE void start( const QString& program );

    Q_INVOKABLE QByteArray readAll() { return QProcess::readAll(); }
    Q_INVOKABLE QByteArray readLine() { return QProcess::readLine(); }

    // if you want to write to an active process, not fully tested!
    Q_INVOKABLE qint64 write( const QString& data ) {
        return QProcess::write( qPrintable( data ) );
    }

 private:
     Q_DISABLE_COPY( Process )
};

#endif // PROCESS_H
