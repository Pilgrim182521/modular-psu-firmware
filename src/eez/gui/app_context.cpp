/*
 * EEZ Modular Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>

#include <eez/gui/app_context.h>

#if OPTION_DISPLAY

// TODO this must be removed from here
#include <eez/modules/psu/psu.h>

#include <eez/modules/psu/devices.h>
#include <eez/modules/psu/idle.h>

#include <eez/modules/psu/gui/psu.h>
//

#include <eez/gui/assets.h>
#include <eez/gui/dialogs.h>
#include <eez/gui/draw.h>
#include <eez/gui/gui.h>
#include <eez/gui/touch.h>
#include <eez/gui/update.h>
#include <eez/gui/widgets/button.h>
#include <eez/index.h>
#include <eez/modules/mcu/display.h>
#include <eez/sound.h>
#include <eez/system.h>

#define CONF_GUI_TOAST_DURATION_MS 2000L

namespace eez {
namespace gui {

AppContext *g_appContext;

////////////////////////////////////////////////////////////////////////////////

AppContext::AppContext() {
#if OPTION_SDRAM
    m_activePage.displayBufferIndex = mcu::display::allocBuffer(true);
#endif

    m_pushProgressPage = false;
    m_popProgressPage = false;
    m_setPageIdOnNextIter = false;
    m_isTopPage = true;
}


void AppContext::stateManagment() {
    if (m_pushProgressPage) {
        data::set(data::Cursor(), DATA_ID_ALERT_MESSAGE, data::Value(m_progressMessage), 0);
        g_appContext->m_dialogCancelCallback = m_progressAbortCallback;
        pushPage(PAGE_ID_PROGRESS);
        m_pushProgressPage = false;
    }

    if (m_popProgressPage) {
        if (getActivePageId() == PAGE_ID_PROGRESS) {
            popPage();
        }
        m_popProgressPage = false;
    }

    if (m_setPageIdOnNextIter) {
        setPage(m_pageIdToSetOnNextIter);
        if (m_pageIdToSetOnNextIter == PAGE_ID_WELCOME) {
            playPowerUp(sound::PLAY_POWER_UP_CONDITION_WELCOME_PAGE_IS_ACTIVE);
        } 
        m_setPageIdOnNextIter = false;
    }

    // call m_checkAsyncOperationStatus
    if (getActivePageId() == PAGE_ID_ASYNC_OPERATION_IN_PROGRESS) {
        if (m_checkAsyncOperationStatus) {
            m_checkAsyncOperationStatus();
        }
    }

    // remove alert message after period of time
    uint32_t inactivityPeriod = psu::idle::getGuiAndEncoderInactivityPeriod();
    if (getActivePageId() == INTERNAL_PAGE_ID_TOAST_MESSAGE) {
        if (inactivityPeriod >= CONF_GUI_TOAST_DURATION_MS) {
            popPage();
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

bool AppContext::isActivePageInternal() {
    return isPageInternal(m_activePage.pageId);
}

bool AppContext::isWidgetActionEnabled(const WidgetCursor &widgetCursor) {
    const Widget *widget = widgetCursor.widget;
    if (widget->action) {
        AppContext *saved = g_appContext;
        g_appContext = this;

        if (isFrontPanelLocked()) {
            int activePageId = getActivePageId();
            if (activePageId == PAGE_ID_KEYPAD ||
                activePageId == PAGE_ID_TOUCH_CALIBRATION_YES_NO ||
                activePageId == PAGE_ID_TOUCH_CALIBRATION_YES_NO_CANCEL) {
                g_appContext = saved;
                return true;
            }
            
            if (widget->action != ACTION_ID_SYS_FRONT_PANEL_UNLOCK) {
                g_appContext = saved;
                return false;
            }
        }

        if (widget->type == WIDGET_TYPE_BUTTON) {
            const ButtonWidget *buttonWidget = GET_WIDGET_PROPERTY(widget, specific, const ButtonWidget *);
            if (!data::get(widgetCursor.cursor, buttonWidget->enabled).getInt()) {
                g_appContext = saved;
                return false;
            }
        }

        g_appContext = saved;
        return true;
    }

    return false;
}

bool AppContext::isAutoRepeatAction(int action) {
    return false;
}

bool AppContext::isFocusWidget(const WidgetCursor &widgetCursor) {
    return false;
}

////////////////////////////////////////////////////////////////////////////////

int AppContext::getActivePageId() {
    return m_activePage.pageId;
}

bool AppContext::isActivePage(int pageId) {
    return pageId == m_activePage.pageId;
}

Page *AppContext::getActivePage() {
    return m_activePage.page;
}

int AppContext::getPreviousPageId() {
    return m_previousPageId;
}

Page *AppContext::getPreviousPage() {
    if (m_pageNavigationStackPointer > 0) {
        return m_pageNavigationStack[m_pageNavigationStackPointer - 1].page;
    } else {
        return 0;
    }
}

void AppContext::onPageChanged() {
    eez::mcu::display::turnOn();
    psu::idle::noteGuiActivity();
}

void AppContext::doShowPage(int index, Page *page) {
    // delete current page
    if (m_activePage.page) {
        m_activePage.page->pageFree();
    }

    m_previousPageId = m_activePage.pageId;

    m_activePage.page = page ? page : getPageFromId(index);
    m_activePage.pageId = index;
    
    if (m_activePage.page) {
        m_activePage.page->pageWillAppear();
    }

    m_showPageTime = micros();

    // clear text message if active page is not PAGE_ID_TEXT_MESSAGE
    if (getActivePageId() != PAGE_ID_TEXT_MESSAGE && m_textMessage[0]) {
        m_textMessage[0] = 0;
    }
    onPageChanged();

    refreshScreen();
}

void AppContext::setPage(int pageId) {
    // delete stack
    for (int i = 0; i < m_pageNavigationStackPointer; ++i) {
        if (m_pageNavigationStack[i].page) {
            m_pageNavigationStack[i].page->pageFree();
        }
#if OPTION_SDRAM
        mcu::display::freeBuffer(m_pageNavigationStack[i].displayBufferIndex);
#endif
    }
    m_pageNavigationStackPointer = 0;

    //
    doShowPage(pageId);
}

void AppContext::replacePage(int pageId, Page *page) {
    doShowPage(pageId, page);
}

void AppContext::pushPage(int pageId, Page *page) {
    // push current page on stack
    if (m_activePage.pageId != INTERNAL_PAGE_ID_NONE) {
        if (m_pageNavigationStackPointer == CONF_GUI_PAGE_NAVIGATION_STACK_SIZE) {
            // no more space on the stack

            // delete page on the bottom
            if (m_pageNavigationStack[0].page) {
                m_pageNavigationStack[0].page->pageFree();
            }
#if OPTION_SDRAM
            mcu::display::freeBuffer(m_pageNavigationStack[0].displayBufferIndex);
#endif

            // move stack one down
            for (int i = 1; i < m_pageNavigationStackPointer; ++i) {
                m_pageNavigationStack[i - 1] = m_pageNavigationStack[i];
            }

            --m_pageNavigationStackPointer;
        }

        m_pageNavigationStack[m_pageNavigationStackPointer] = m_activePage;
        ++m_pageNavigationStackPointer;

#if OPTION_SDRAM
        m_activePage.displayBufferIndex = mcu::display::allocBuffer();
#endif
    }

    doShowPage(pageId, page);
}

void AppContext::popPage() {
    if (m_pageNavigationStackPointer > 0) {
        --m_pageNavigationStackPointer;
#if OPTION_SDRAM
        mcu::display::freeBuffer(m_activePage.displayBufferIndex);
        m_activePage.displayBufferIndex = m_pageNavigationStack[m_pageNavigationStackPointer].displayBufferIndex;
#endif
        doShowPage(m_pageNavigationStack[m_pageNavigationStackPointer].pageId, m_pageNavigationStack[m_pageNavigationStackPointer].page);
    } else {
        doShowPage(getMainPageId());
    }
}

Page *AppContext::getPage(int pageId) {
    if (m_activePage.pageId == pageId) {
        return m_activePage.page;
    }

    for (int i = 0; i < m_pageNavigationStackPointer; ++i) {
        if (m_pageNavigationStack[i].pageId == pageId) {
            return m_pageNavigationStack[i].page;
        }
    }

    return nullptr;
}

bool AppContext::isPageActiveOrOnStack(int pageId) {
    return getPage(pageId) != nullptr;
}

void AppContext::showPage(int pageId) {
	if (pageId != getActivePageId()) {
		setPage(pageId);
	}
}

void AppContext::showPageOnNextIter(int pageId) {
    m_setPageIdOnNextIter = true;
    m_pageIdToSetOnNextIter = pageId;
}

void AppContext::pushSelectFromEnumPage(const data::EnumItem *enumDefinition, uint16_t currentValue,
                                        bool (*disabledCallback)(uint16_t value),
                                        void (*onSet)(uint16_t)) {
	m_selectFromEnumPage.init(enumDefinition, currentValue, disabledCallback, onSet);
    pushPage(INTERNAL_PAGE_ID_SELECT_FROM_ENUM, &m_selectFromEnumPage);
}

void AppContext::pushSelectFromEnumPage(void (*enumDefinitionFunc)(data::DataOperationEnum operation, data::Cursor &cursor, data::Value &value),
                                        uint16_t currentValue, bool (*disabledCallback)(uint16_t value), void (*onSet)(uint16_t)) {
	m_selectFromEnumPage.init(enumDefinitionFunc, currentValue, disabledCallback, onSet);
    pushPage(INTERNAL_PAGE_ID_SELECT_FROM_ENUM, &m_selectFromEnumPage);
}

////////////////////////////////////////////////////////////////////////////////

bool AppContext::testExecuteActionOnTouchDown(int action) {
    return false;
}

uint16_t AppContext::getWidgetBackgroundColor(const WidgetCursor &widgetCursor,
                                              const Style *style) {
    return style->background_color;
}

bool AppContext::isBlinking(const data::Cursor &cursor, uint16_t id) {
    return false;
}

void AppContext::onScaleUpdated(int dataId, bool scaleIsVertical, int scaleWidth,
                                float scaleHeight) {
}

uint32_t AppContext::getNumHistoryValues(uint16_t id) {
    return 0;
}

uint32_t AppContext::getCurrentHistoryValuePosition(const Cursor &cursor, uint16_t id) {
    return 0;
}

Value AppContext::getHistoryValue(const Cursor &cursor, uint16_t id, uint32_t position) {
    return Value();
}

bool AppContext::isActiveWidget(const WidgetCursor &widgetCursor) {
    return false;
}

void AppContext::onPageTouch(const WidgetCursor &foundWidget, Event &touchEvent) {
}

////////////////////////////////////////////////////////////////////////////////

void AppContext::updatePage(WidgetCursor &widgetCursor) {
#if OPTION_SDRAM
    int selectedBufferIndexSaved = mcu::display::selectBuffer(m_activePage.displayBufferIndex);
#endif

    int x;
    int y;
    int width;
    int height;
    bool withShadow;

    if (isPageInternal(m_activePage.pageId)) {
        InternalPage *internalPage = ((InternalPage *)g_appContext->getActivePage());
        
        if (!widgetCursor.previousState) {
            internalPage->refresh();
        }
        internalPage->updatePage();

        x = internalPage->x;
        y = internalPage->y;
        width = internalPage->width;
        height = internalPage->height;
        withShadow = true;
    } else {
		const Widget *page = getPageWidget(m_activePage.pageId);

		auto savedPreviousState = widgetCursor.previousState;
        auto savedWidget = widgetCursor.widget;

        x = widgetCursor.x + page->x;
        y = widgetCursor.y + page->y;
        width = page->w;
        height = page->h;
        withShadow = page->x > 0;

        if (!widgetCursor.previousState) {
            // clear background
            const Style* style = getStyle(page->style);
            mcu::display::setColor(style->background_color);
            mcu::display::fillRect(x, y, x + width - 1, y + height - 1);
        }

        widgetCursor.widget = page;
        enumWidget(widgetCursor, drawWidgetCallback);

		widgetCursor.widget = savedWidget;
		widgetCursor.previousState = savedPreviousState;
    }

#if OPTION_SDRAM
    mcu::display::drawBuffer(x, y, width, height, withShadow);
    
    mcu::display::selectBuffer(selectedBufferIndexSaved);
#endif
}

bool isRect1FullyCoveredByRect2(int xRect1, int yRect1, int wRect1, int hRect1, int xRect2, int yRect2, int wRect2, int hRect2) {
    return xRect2 <= xRect1 && 
        yRect2 <= yRect1 &&
        xRect2 + wRect2 >= xRect1 + wRect1 &&
        yRect2 + hRect2 >= yRect1 + hRect1;
}

void getPageRect(int pageId, Page *page, int &x, int &y, int &w, int &h) {
    if (isPageInternal(pageId)) {
        x = ((InternalPage *)page)->x;
        y = ((InternalPage *)page)->y;
        w = ((InternalPage *)page)->width;
        h = ((InternalPage *)page)->height;
    } else {
        const Widget *page = getPageWidget(pageId);
        x = page->x;
        y = page->y;
        w = page->w;
        h = page->h;
    }
}

bool AppContext::isPageFullyCovered(int pageNavigationStackIndex) {
    int xPage, yPage, wPage, hPage;
    getPageRect(m_pageNavigationStack[pageNavigationStackIndex].pageId, m_pageNavigationStack[pageNavigationStackIndex].page, xPage, yPage, wPage, hPage);

    for (int i = pageNavigationStackIndex + 1; i <= m_pageNavigationStackPointer; i++) {
        int xPageAbove, yPageAbove, wPageAbove, hPageAbove;

        if (i == m_pageNavigationStackPointer) {
            getPageRect(m_activePage.pageId, m_activePage.page, xPageAbove, yPageAbove, wPageAbove, hPageAbove);
        } else {
            getPageRect(m_pageNavigationStack[i].pageId, m_pageNavigationStack[i].page, xPageAbove, yPageAbove, wPageAbove, hPageAbove);
        }

        if (isRect1FullyCoveredByRect2(xPage, yPage, wPage, hPage, xPageAbove, yPageAbove, wPageAbove, hPageAbove)) {
            return true;
        }
    }

    return false;
}

void AppContext::updateAppView(WidgetCursor &widgetCursor) {
    if (m_activePage.pageId == INTERNAL_PAGE_ID_NONE) {
        return;
    }

#if OPTION_SDRAM
    widgetCursor.cursor = Cursor();
    updatePage(widgetCursor);
    widgetCursor.nextState();

    m_activePageSaved = m_activePage;
    m_isTopPage = false;

    for (int i = m_pageNavigationStackPointer - 1; i >= 0; i--) {
        if (!isPageFullyCovered(i)) {
            bool paintedSaved = mcu::display::g_painted;
            mcu::display::g_painted = false;

            m_activePage = m_pageNavigationStack[i];

            widgetCursor.cursor = Cursor();
            updatePage(widgetCursor);
            widgetCursor.nextState();

            mcu::display::g_painted = paintedSaved || mcu::display::g_painted;
        }
    }

    m_isTopPage = true;
    m_activePage = m_activePageSaved;
    m_activePageSaved = PageOnStack();
#else
    m_activePageSaved = m_activePage;
    m_isTopPage = false;

    for (int i = 0; i < m_pageNavigationStackPointer; ++i) {
        if (!isPageFullyCovered(i)) {
            bool paintedSaved = mcu::display::g_painted;
            mcu::display::g_painted = false;

            m_activePage = m_pageNavigationStack[i];

            widgetCursor.cursor = Cursor();
            updatePage(widgetCursor);
            widgetCursor.nextState();

            mcu::display::g_painted = paintedSaved || mcu::display::g_painted;
        }
    }

    m_isTopPage = true;
    m_activePage = m_activePageSaved;
    m_activePageSaved = PageOnStack();
    
    widgetCursor.cursor = Cursor();
    updatePage(widgetCursor);
    widgetCursor.nextState();
#endif
}

void AppContext::showProgressPage(const char *message, void (*abortCallback)()) {
    m_progressMessage = message;
    m_progressAbortCallback = abortCallback;
    m_pushProgressPage = true;
}

bool AppContext::updateProgressPage(size_t processedSoFar, size_t totalSize) {
    if (totalSize > 0) {
        g_progress = data::Value((int)round((processedSoFar * 1.0f / totalSize) * 100.0f), VALUE_TYPE_PERCENTAGE);
    } else {
        g_progress = data::Value((uint32_t)processedSoFar, VALUE_TYPE_SIZE);
    }

    if (m_pushProgressPage) {
        return true;
    }

    if (m_activePage.pageId == PAGE_ID_PROGRESS || m_activePageSaved.pageId == PAGE_ID_PROGRESS) {
        return true;
    }

    return false;
}

void AppContext::hideProgressPage() {
    m_popProgressPage = true;
}

} // namespace gui
} // namespace eez

#endif
