#ifndef TYPEXMLBUFF_H_HEAD__FILE__
#define TYPEXMLBUFF_H_HEAD__FILE__

#pragma once
#include "TypeFile.h"

class TYPEFILE_EXPORT typeFile::XmlBuff {
	/// @brief 所有节点
	QSharedPointer<type::XmlNode> node;

public:
	XmlBuff() {
	}

	void setXmlNode(QSharedPointer<type::XmlNode> node) {
		this->node = node;
	}

	QSharedPointer<type::XmlNode> getNode() {
		return this->node;
	}
};

#endif // TYPEXMLBUFF_H_HEAD__FILE__
