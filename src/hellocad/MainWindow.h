/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace hellocad
{
	class MainWindowPrivate;
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		MainWindow(QWidget * parent = nullptr);
		~MainWindow();

	protected:
		Q_DECLARE_PRIVATE(MainWindow);
		QScopedPointer<MainWindowPrivate> d_ptr;
	};
}

