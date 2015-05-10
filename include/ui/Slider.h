//
// Slider.h
// Vorb Engine
//
// Created by Benjamin Arnold on 5 May 2015
// Copyright 2014 Regrowth Studios
// All Rights Reserved
//

/*! \file Slider.h
* @brief 
* Defines the slider widget.
*
*/

#pragma once

#ifndef Vorb_Slider_h__
//! @cond DOXY_SHOW_HEADER_GUARDS
#define Vorb_Slider_h__
//! @endcond

#ifndef VORB_USING_PCH
#include "types.h"
#endif // !VORB_USING_PCH

#include "Drawables.h"
#include "Widget.h"

namespace vorb {
    namespace ui {

        /// Forward Declarations
        class UIRenderer;

        class Slider : public Widget {
        public:
            /*! @brief Default constructor. */
            Slider();
            /*! @brief Constructor that sets name, position, and dimensions.
            *
            * @param name: Name of the control.
            * @param destRect: Rectangle defining the position and dimensions as the tuple <x,y,w,h>.
            */
            Slider(const nString& name, const f32v4& destRect = f32v4(0));
            /*! @brief Constructor that sets parent control, name, position, and dimensions.
            *
            * The control will be made a child of parent.
            *
            * @param parent: Parent control object.
            * @param name: Name of the control.
            * @param destRect: Rectangle defining the position and dimensions as the tuple <x,y,w,h>.
            */
            Slider(Widget* parent, const nString& name, const f32v4& destRect = f32v4(0));
            /*! @brief Default destructor. */
            virtual ~Slider();

            /*! @brief Adds all drawables to the UIRenderer
            *
            * @param renderer: UIRenderer to add to
            */
            virtual void addDrawables(UIRenderer* renderer) override;

            /*! @brief Removes all drawables from the UIRenderer
            *
            * @param renderer: UIRenderer to remove from
            */
            virtual void removeDrawables(UIRenderer* renderer) override;

            /************************************************************************/
            /* Getters                                                              */
            /************************************************************************/
            virtual const VGTexture& getSlideTexture() const { return m_drawableSlide.getTexture(); }
            virtual const VGTexture& getBarTexture() const { return m_drawableBar.getTexture(); }
            virtual const color4& getSlideColor() const { return m_slideColor; }
            virtual const color4& getSlideHoverColor() const { return m_slideHoverColor; }
            virtual const color4& getBarColor() const { return m_barColor; }
            virtual const int& getValue() const { return m_value; }
            virtual const int& getMin() const { return m_min; }
            virtual const int& getMax() const { return m_max; }
            /// Gets slider value scaled between 0.0f and 1.0f
            virtual f32 getValueScaled() const { return (f32)(m_value - m_min) / (m_max - m_min); }

            /************************************************************************/
            /* Setters                                                              */
            /************************************************************************/
            virtual void setSlideDimensions(const f32v2& dimensions);
            virtual void setDimensions(const f32v2& dimensions) override;
            virtual void setHeight(f32 height) override;
            virtual void setPosition(const f32v2& position) override;
            virtual void setSlideTexture(VGTexture texture);
            virtual void setBarTexture(VGTexture texture);
            virtual void setBarColor(const color4& color);
            virtual void setWidth(f32 width) override;
            virtual void setX(f32 x) override;
            virtual void setY(f32 y) override;
            virtual void setSlideColor(const color4& color);
            virtual void setSlideHoverColor(const color4& color);
            virtual void setValue(int value);
            virtual void setRange(int min, int max);
            virtual void setMin(int min);
            virtual void setMax(int max);

            virtual bool isInSlideBounds(const f32v2& point) { return isInBounds(point.x, point.y); }
            virtual bool isInSlideBounds(f32 x, f32 y);

            /************************************************************************/
            /* Events                                                               */
            /************************************************************************/
            Event<int> ValueChange; ///< Occurs when the value changes

        protected:
            virtual void updateSlidePosition();
            virtual void updateColor();
            virtual void refreshDrawables();

            /************************************************************************/
            /* Event Handlers                                                       */
            /************************************************************************/
            virtual void onMouseDown(Sender s, const MouseButtonEvent& e) override;
            virtual void onMouseUp(Sender s, const MouseButtonEvent& e) override;
            virtual void onMouseMove(Sender s, const MouseMotionEvent& e) override;

            DrawableRect m_drawableBar, m_drawnBar;
            DrawableRect m_drawableSlide, m_drawnSlide;
            color4 m_barColor = color::LightGray;
            color4 m_slideColor = color::DarkGray, m_slideHoverColor = color::LightSlateGray;
            int m_value = 0;
            int m_min = 0;
            int m_max = 10;
        };
    }
}
namespace vui = vorb::ui;

#endif // !Vorb_Slider_h__
