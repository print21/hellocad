/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QTreeWidget>

class QSpinBox;
class QLineEdit;
class QDoubleSpinBox;

namespace common
{
	class FeatureBase;
	class AttributeBase;
	class AttributeInteger;
	class AttributeString;
	class AttributeReal;
}

namespace hellocad
{
	class AttributeViewPrivate;
	class AttributeView : public QTreeWidget
	{
		Q_OBJECT;
	public:
		explicit AttributeView(QWidget * parent = nullptr);
		~AttributeView();

		void setFeature(const common::FeatureBase * feature);

	private:
		Q_DECLARE_PRIVATE(AttributeView);
		const QScopedPointer<AttributeViewPrivate> d_ptr;
	};

	class AttributeIntegerWidget : public QWidget
	{
		Q_OBJECT;
	public:
		AttributeIntegerWidget(common::AttributeInteger* variant, bool readonly, QWidget* parent = nullptr);
		~AttributeIntegerWidget();

	protected Q_SLOTS:
		void slotSpinBoxFinishEdit();
		void slotAttributeValueChanged(const common::AttributeBase* sender);

	protected:
		common::AttributeInteger* _attribute;
		QSpinBox* _spinBox;
		QMetaObject::Connection _variantChangeConnect;
	};

	class AttributeRealWidget : public QWidget
	{
		Q_OBJECT;
	public:
		AttributeRealWidget(common::AttributeReal* variant, bool readonly, QWidget* parent = nullptr);
		~AttributeRealWidget();

	protected Q_SLOTS:
		void slotSpinBoxFinishEdit();
		void slotAttributeValueChanged(const common::AttributeBase* sender);

	protected:
		common::AttributeReal* _attribute;
		QDoubleSpinBox* _spinBox;
		QMetaObject::Connection _variantChangeConnect;
	};

	class AttributeStringWidget : public QWidget
	{
		Q_OBJECT;
	public:
		AttributeStringWidget(common::AttributeString* variant, bool readonly, QWidget* parent = nullptr);
		~AttributeStringWidget();

	protected Q_SLOTS:
		void slotLineEditFinished();
		void slotAttributeValueChanged(const common::AttributeBase* sender);

	protected:
		common::AttributeString* _attribute;
		QLineEdit* _lineEdit;
		QMetaObject::Connection _variantChangeConnect;
	};
}

