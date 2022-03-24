/*
 *HelloCAD a simple cad platform
 */

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace hellocad
{
	class AttributeView;

	class MainWindowPrivate;
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		MainWindow(QWidget * parent = nullptr);
		~MainWindow();

		static MainWindow* mainWindow();

		AttributeView* attributeView() const;

	protected:
		void initWindow();

		void initToolBar();

		virtual void closeEvent(QCloseEvent* event) override;

	protected Q_SLOTS:
		void slotNewDocument();
		void slotCreateCube();
		void slotCreateSphere();
		void slotUpdateDocument();

	protected:
		Q_DECLARE_PRIVATE(MainWindow);
		QScopedPointer<MainWindowPrivate> d_ptr;
	};
}

