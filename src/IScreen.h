#pragma once

#include "IControl.h"

#include <memory>
#include <vector>
#include <string>

class CApp;

class IScreen {
public:
	IScreen( std::string name );

	virtual void VPopulateControls() = 0;

	void StepControls();

	void DrawControls();

	void AddControl( IControl *control );

	friend class CApp;

	std::string m_name;
protected:
	CApp *m_app;

	std::vector< std::shared_ptr< IControl > > m_controls;
};