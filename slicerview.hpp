#ifndef SLICERVIEW_HPP
#define SLICERVIEW_HPP

#include "slicerdocument.hpp"
#include "previewwindow.hpp"
#include <gtkmm/flowbox.h>

namespace Slicer {

class View : public Gtk::FlowBox {
public:
    View(Slicer::Document& document);
    virtual ~View(){};

private:
    void onChildActivated(Gtk::FlowBoxChild* child);

    Slicer::Document& m_document;
    std::unique_ptr<Slicer::PreviewWindow> m_previewWindow;
};
}

#endif // SLICERVIEW_HPP
