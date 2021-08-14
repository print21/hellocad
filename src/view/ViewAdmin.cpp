/*
 *HelloCAD a simple cad platform
*/

#include "ViewAdmin.h"
#include "ViewDocument.h"

namespace view
{
	QScopedPointer<Admin> Admin::_ptr(nullptr);

	class AdminPrivate
	{
	public:
		AdminPrivate() { ; }
		~AdminPrivate() { ; }

		//std::map<const common::DocumentBase *, ViewDocument *> _docMap;
	};
}

using namespace view;

Admin::Admin()
	:d_ptr(new AdminPrivate())
{

}

Admin::~Admin()
{
}

void Admin::init()
{
	Q_ASSERT(Admin::_ptr == nullptr);
	Admin::_ptr.reset(new Admin());

	//connect signals
}

Admin & Admin::instance()
{
	return *(Admin::_ptr);
}

