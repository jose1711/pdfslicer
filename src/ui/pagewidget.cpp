// PDF Slicer
// Copyright (C) 2017-2018 Julián Unrrein

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "pagewidget.hpp"
#include <iostream>

namespace Slicer {

PageWidget::PageWidget(const Glib::RefPtr<Page>& page,
                       int targetSize)
    : m_page{page}
    , m_targetSize{targetSize}
{
    setupWidgets();
}

void PageWidget::changeSize(int targetSize)
{
    m_targetSize = targetSize;

    const Page::Size pageSize = m_page->scaledRotatedSize(m_targetSize);
    set_size_request(pageSize.width, pageSize.height);
}

void PageWidget::setupWidgets()
{
    const Page::Size pageSize = m_page->scaledRotatedSize(m_targetSize);
    set_size_request(pageSize.width, pageSize.height);
    set_valign(Gtk::ALIGN_CENTER);
    set_halign(Gtk::ALIGN_CENTER);

    m_spinner.set_size_request(38, 38);
    m_spinner.start();
    m_contentBox.pack_start(m_spinner, true, false);

    m_overlay.set_halign(Gtk::ALIGN_CENTER);
    m_overlay.set_valign(Gtk::ALIGN_CENTER);
    m_overlay.add(m_thumbnail);
    m_overlayEventBox.add(m_overlay);

    add(m_contentBox);

    show_all();
}

void PageWidget::renderPage()
{
    m_thumbnail.set(m_page->renderPage(m_targetSize));
}

void PageWidget::showSpinner()
{
    if (!m_spinner.is_visible()) {
        m_spinner.show();
        m_spinner.start();
        m_contentBox.remove(m_overlayEventBox);
    }
}

void PageWidget::showPage()
{
    if (!isThumbnailVisible()) {
        m_spinner.stop();
        m_contentBox.pack_start(m_overlayEventBox, Gtk::PACK_SHRINK);
        m_overlayEventBox.show_all();
        m_spinner.hide();
    }
}

bool PageWidget::isThumbnailVisible()
{
    return m_overlayEventBox.get_parent() != nullptr;
}

} // namespace Slicer