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
		void initToolBar();

		virtual void closeEvent(QCloseEvent* event) override;

	protected Q_SLOTS:
		void slotNewDocument();
		void slotCreateCube();

	protected:
		Q_DECLARE_PRIVATE(MainWindow);
		QScopedPointer<MainWindowPrivate> d_ptr;
	};
}

