/*
 *HelloCAD a simple cad platform
 */

#include "AttributeView.h"

#include <common/FeatureBase.h>
#include <common/AttributeBase.h>
#include <common/AttributeReal.h>
#include <common/AttributeString.h>
#include <common/AttributeInteger.h>
#include <common/AttributeBoolean.h>

#include <QHeaderView>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>

namespace hellocad
{
	class AttributeViewPrivate
	{
	public:
		AttributeViewPrivate(){;}
		~AttributeViewPrivate(){;}

		const common::FeatureBase* _feature;
	};
}

using namespace hellocad;

AttributeView::AttributeView(QWidget* parent /* = nullptr */)
	:QTreeWidget(parent), d_ptr(new AttributeViewPrivate())
{
	this->setDragEnabled(false);
	this->setAcceptDrops(false);
	this->setDropIndicatorShown(false);
	this->setRootIsDecorated(true);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setAlternatingRowColors(true);

	this->header()->setStretchLastSection(true);
	this->header()->setVisible(true);

	QStringList labels;
	labels << tr("Attribute") << tr("Value");
	this->setHeaderLabels(labels);
}

AttributeView::~AttributeView()
{

}

void AttributeView::setFeature(const common::FeatureBase* feature)
{
	Q_D(AttributeView);

	if (d->_feature != nullptr)
	{
		this->clear();
	}

	d->_feature = feature;
	if (feature == nullptr)
	{
		return;
	}

	QStringList inputNames = feature->attributeNames();
	for (int i = 0; i < inputNames.size(); ++i)
	{
		const QString& name = inputNames.at(i);

		QTreeWidgetItem* item = new QTreeWidgetItem(this);
		item->setText(0, name);
		item->setFlags(Qt::ItemFlag(item->flags() | ~Qt::ItemIsEditable));

		this->addTopLevelItem(item);
		common::AttributeBase* var = feature->attribute<common::AttributeBase>(name);

#if 0
		std::vector<std::string> connectedPorts;
		std::vector<const common::FeatureBase*> connected = filter->inputConnections(name, &connectedPorts);
		if (!connected.empty())
		{
			if (connected.size() == 1)
			{
				item->setText(1, QString::fromUtf8("From %1:%2").arg(connected.front()->keyName().c_str()).arg(connectedPorts.front().c_str()));
			}
			else
			{
				QString strCache = QString::fromUtf8("From [");

				for (size_t f = 0; f < connected.size(); ++f)
				{
					strCache += QString::fromUtf8("%1:%2,").arg(connected[f]->keyName().c_str()).arg(connectedPorts[f].c_str());
				}
				strCache[strCache.size() - 1] = QChar::fromLatin1(']');
				item->setText(1, strCache);
			}
		}
		else
#endif
		if (var != nullptr)
		{
			if (strcmp(var->variantTypeName(), QMetaType::typeName(qMetaTypeId<int>())) == 0)
			{
				this->setItemWidget(item, 1, new AttributeIntegerWidget(
					dynamicCast<common::AttributeInteger>(const_cast<common::AttributeBase*>(var)), false, this));
			}
			else if (strcmp(var->variantTypeName(), QMetaType::typeName(qMetaTypeId<QString>())) == 0)
			{
				this->setItemWidget(item, 1, new AttributeStringWidget(
					dynamicCast<common::AttributeString>(const_cast<common::AttributeBase*>(var)), false, this));
			}
			else if (strcmp(var->variantTypeName(), QMetaType::typeName(qMetaTypeId<double>())) == 0)
			{
				this->setItemWidget(item, 1, new AttributeRealWidget(
					dynamicCast<common::AttributeReal>(const_cast<common::AttributeBase*>(var)), false, this));
			}
			else
			{
				item->setText(1, var->variantTypeName());
			}
		}
	}

	this->expandAll();
}

//////////////////////////////////////////////////////////////////////////
AttributeIntegerWidget::AttributeIntegerWidget(common::AttributeInteger* variant, bool readonly, QWidget* parent /*= nullptr*/)
	:_attribute(variant), QWidget(parent)
{
	_spinBox = new QSpinBox(this);
	_spinBox->setMinimum(-std::numeric_limits<int>::max());
	_spinBox->setMaximum(std::numeric_limits<int>::max());
	_spinBox->setSingleStep(1);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(_spinBox);

	layout->setMargin(0);
	this->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	_spinBox->setReadOnly(readonly);
	if (_attribute->isValid())
	{
		_spinBox->setValue(variant->value());
	}
	else
	{
		_spinBox->setValue(0);
	}

	connect(_spinBox, &QSpinBox::editingFinished, this, &AttributeIntegerWidget::slotSpinBoxFinishEdit);
	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeIntegerWidget::slotAttributeValueChanged);
}

AttributeIntegerWidget::~AttributeIntegerWidget()
{
	//qDebug() << "Destruct varint integer widget";
}

void AttributeIntegerWidget::slotSpinBoxFinishEdit()
{
	this->disconnect(_variantChangeConnect);

	_attribute->setValue(_spinBox->value());

	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeIntegerWidget::slotAttributeValueChanged);
}

void AttributeIntegerWidget::slotAttributeValueChanged(const common::AttributeBase* sender)
{
	_spinBox->blockSignals(true);

	_spinBox->setValue(_attribute->value());

	_spinBox->blockSignals(false);
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
AttributeRealWidget::AttributeRealWidget(common::AttributeReal* variant, bool readonly, QWidget* parent /*= nullptr*/)
	:_attribute(variant), QWidget(parent)
{
	_spinBox = new QDoubleSpinBox(this);
	_spinBox->setMinimum(-std::numeric_limits<double>::max());
	_spinBox->setMaximum(std::numeric_limits<double>::max());
	_spinBox->setSingleStep(1);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(_spinBox);

	layout->setMargin(0);
	this->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	_spinBox->setReadOnly(readonly);
	if (_attribute->isValid())
	{
		_spinBox->setValue(variant->value());
	}
	else
	{
		_spinBox->setValue(0);
	}

	connect(_spinBox, &QSpinBox::editingFinished, this, &AttributeRealWidget::slotSpinBoxFinishEdit);
	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeRealWidget::slotAttributeValueChanged);
}

AttributeRealWidget::~AttributeRealWidget()
{
	//qDebug() << "Destruct varint integer widget";
}

void AttributeRealWidget::slotSpinBoxFinishEdit()
{
	this->disconnect(_variantChangeConnect);

	_attribute->setValue(_spinBox->value());

	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeRealWidget::slotAttributeValueChanged);
}

void AttributeRealWidget::slotAttributeValueChanged(const common::AttributeBase* sender)
{
	_spinBox->blockSignals(true);

	_spinBox->setValue(_attribute->value());

	_spinBox->blockSignals(false);
}

//////////////////////////////////////////////////////////////////////////

AttributeStringWidget::AttributeStringWidget(common::AttributeString* variant, bool readonly, QWidget* parent /*= nullptr*/)
	:_attribute(variant), QWidget(parent)
{
	_lineEdit = new QLineEdit(this);
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(_lineEdit);

	layout->setMargin(0);
	this->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	_lineEdit->setReadOnly(readonly);
	if (_attribute->isValid())
	{
		_lineEdit->setText(variant->value());
	}

	connect(_lineEdit, &QLineEdit::editingFinished, this, &AttributeStringWidget::slotLineEditFinished);
	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeStringWidget::slotAttributeValueChanged);
}

AttributeStringWidget::~AttributeStringWidget()
{

}

void AttributeStringWidget::slotLineEditFinished()
{
	this->disconnect(_variantChangeConnect);

	_attribute->setValue(_lineEdit->text());

	_variantChangeConnect = connect(_attribute, &common::AttributeBase::signalValueChanged, this, &AttributeStringWidget::slotAttributeValueChanged);
}

void AttributeStringWidget::slotAttributeValueChanged(const common::AttributeBase* sender)
{
	_lineEdit->blockSignals(true);

	_lineEdit->setText(_attribute->value());

	_lineEdit->blockSignals(false);
}
