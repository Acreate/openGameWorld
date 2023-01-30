#include <QCoreApplication>
#include "ProcessArgs.h"
#include "typeFile.h"
#include "typeText.h"
#include "typeTextBuff.h"
int main(int argc, char* argv[]) {
	ProcessArgs process( argc, argv );
	auto textInstance = typeFile::generate::textInstance( "abcTest.txt" );
	qsizetype writeContents = textInstance->writeContents( "123456" );
	QString strContent = "987654321";
	qsizetype writeContents2 = textInstance->writeContents( strContent, 1024 );

	qsizetype length = strContent.length();
	auto textBuff = textInstance->getTextBuff();
	*textBuff << "你好";
	qsizetype length3 = textInstance->writeContentsAtTextBuffInstance();
	return 0;
}
