/*
* HelloCAD a simple cad platform
*/

#pragma once

#include <QObject>

namespace view
{
	class AdminPrivate;
	class Admin : public QObject
	{
		Q_OBJECT
	public:
		~Admin();

		static void init();
		static Admin & instance();

	protected:
		Admin();
		static QScopedPointer<Admin> _ptr;

	private:
		Q_DECLARE_PRIVATE(Admin);
		const QScopedPointer<AdminPrivate> d_ptr;
	};
}


