#ifndef TYPEXMLNODE_H_HEAD__FILE__
#define TYPEXMLNODE_H_HEAD__FILE__

#pragma once
#include "TypeFile.h"

class TYPEFILE_EXPORT typeFile::type::XmlNode {
	QSharedPointer<QString> nodeName;
	/// @brief 属性列表
	QSharedPointer<QMap<QString, QSharedPointer<QVector<QString>>>> nodePropertys = QSharedPointer<QMap<QString, QSharedPointer<QVector<QString>>>>( new QMap<QString, QSharedPointer<QVector<QString>>> );
	/// @brief 子节点列表
	QSharedPointer<QVector<QSharedPointer<XmlNode>>> nodeChildren = QSharedPointer<QVector<QSharedPointer<XmlNode>>>( new QVector<QSharedPointer<XmlNode>>() );
	/// @brief 节点内容
	QSharedPointer<QString> content = QSharedPointer<QString>( new QString );

public:
	/// @brief 创建节点，该节点必须存在一个名称
	/// @param nodeName 
	explicit XmlNode(const QSharedPointer<QString> nodeName)
		: nodeName( nodeName ) {
	}

	explicit XmlNode(const QString& nodeName)
		: nodeName( QSharedPointer<QString>( new QString( nodeName ) ) ) {
	}

	explicit XmlNode(const XmlNode& other) {
		nodeName = QSharedPointer<QString>( new QString( *other.nodeName ) );
		*nodePropertys = *other.nodePropertys;
		*nodeChildren = *other.nodeChildren;
		*content = *other.content;
	}

	explicit XmlNode(const QSharedPointer<XmlNode> other) {
		nodeName = QSharedPointer<QString>( new QString( *other->nodeName ) );
		*nodePropertys = *other->nodePropertys;
		*nodeChildren = *other->nodeChildren;
		*content = *other->content;
	}

	XmlNode& operator=(const QString& name) {
		*nodeName = name;
		return *this;
	}

	/// @brief 追加节点到子节点到列表当中，并且返回子节点个数
	/// @param children 追加的子节点
	/// @return 节点个数
	qsizetype appendChildren(const XmlNode& children) {
		nodeChildren->append( QSharedPointer<XmlNode>( new XmlNode( children ) ) );
		return nodeChildren->size();
	}

	/// @brief 追加节点到子节点到列表当中，并且返回子节点个数
	/// @param children 追加的子节点
	/// @return 节点个数
	qsizetype appendChildren(const QSharedPointer<XmlNode> children) {
		nodeChildren->append( QSharedPointer<XmlNode>( new XmlNode( children ) ) );
		return nodeChildren->size();
	}

	virtual ~XmlNode() {
	}
};

#endif // TYPEXMLNODE_H_HEAD__FILE__
