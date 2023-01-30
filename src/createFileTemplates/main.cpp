#include <QCoreApplication>
#include "ProcessArgs.h"
#include "TypeFile.h"

int main(int argc, char* argv[]) {
	ProcessArgs process( argc, argv );
	TypeFile typeFile;
	auto textInstance = typeFile.getTextInstance( "abcTest.txt" );
	qsizetype writeContents = textInstance->writeTextContents( "123456" );
	QString strContent = "987654321";
	qsizetype writeContents2 = textInstance->writeTextContents( strContent, 1024 );

	qsizetype length = strContent.length();
	auto textBuff = textInstance->getTextBuff();
	textBuff << "你好";
	qsizetype length3 = textInstance->writeTextBuffInstanceContents();
	return 0;
}
