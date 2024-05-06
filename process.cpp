#include "process.h"

void Process::start( const QString& program, const QVariantList& arguments ) {
    QStringList args;

    // convert QVariantList from QML to QStringList for QProcess
    for ( const auto& temp : arguments ) {
        args << temp.toString();
    }

    QProcess::setProcessChannelMode( QProcess::MergedChannels );
    QProcess::start( program, args );
 }

 // If wan to start without arguments for Qt > 5.14
void Process::start( const QString& program ) {

    QProcess::setProcessChannelMode( QProcess::MergedChannels );
    QProcess::setProgram( program );
    QProcess::start();
    QProcess::open( QProcess::ReadWrite );
}
