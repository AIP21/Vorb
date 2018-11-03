//
// Button.h
// Vorb Engine
//
// Created by Benjamin Arnold on 2 May 2015
// Copyright 2014 Regrowth Studios
// MIT License
//

/*! \file Button.h
* \brief 
* Abstract base class for all button widget.
*
*/

#pragma once

#ifndef Vorb_Button_h__
//! @cond DOXY_SHOW_HEADER_GUARDS
#define Vorb_Button_h__
//! @endcond

#ifndef VORB_USING_PCH
#include "Vorb/types.h"
#endif // !VORB_USING_PCH

#include "Vorb/ui/Drawables.h"
#include "Vorb/ui/Widget.h"

namespace vorb {
    namespace ui {

        /// Forward Declarations
        class UIRenderer;

        class Button : public Widget {
        public:
            /*! \brief Default constructor. */
            Button();
            /*! \brief Default destructor. */
            virtual ~Button();

            /*! \brief Adds all drawables to the UIRenderer */
            virtual void addDrawables() override;
            /*! \brief Refresh drawables. */
            virtual void refreshDrawables() override;

            /************************************************************************/
            /* Getters                                                              */
            /************************************************************************/
            virtual      const VGTexture& getTexture()        const { return m_drawableRect.getTexture();   }
            virtual const vg::SpriteFont* getFont()           const { return m_drawableText.getFont();      }
            virtual         const color4& getBackColor()      const { return m_backColor1;                  }
            virtual         const color4& getBackHoverColor() const { return m_backHoverColor1;             }
            virtual         const color4& getTextColor()      const { return m_textColor;                   }
            virtual         const color4& getTextHoverColor() const { return m_textHoverColor;              }
            virtual        const nString& getText()           const { return m_drawableText.getText();      }
            virtual  const vg::TextAlign& getTextAlign()      const { return m_drawableText.getTextAlign(); }
            virtual          const f32v2& getTextScale()      const { return m_drawableText.getTextScale(); }

            /************************************************************************/
            /* Setters                                                              */
            /************************************************************************/
            virtual void setFont(const vg::SpriteFont* font);
            virtual void setTexture(VGTexture texture);
            virtual void setBackColor(const color4& color);
            virtual void setBackColorGrad(const color4& color1, const color4& color2, vg::GradientType grad);
            virtual void setBackHoverColor(const color4& color);
            virtual void setBackHoverColorGrad(const color4& color1, const color4& color2, vg::GradientType grad);
            virtual void setText(const nString& text);
            virtual void setTextColor(const color4& color);
            virtual void setTextHoverColor(const color4& color);
            virtual void setTextAlign(vg::TextAlign textAlign);
            virtual void setTextScale(const f32v2& textScale);

        protected:
            virtual void calculateDrawables() override;

            /*! Updates the colours set for the drawables. */
            virtual void updateColor();
            /*! Updates the text position in the drawable. */
            virtual void updateTextPosition();

            virtual void onMouseMove(Sender s, const MouseMotionEvent& e) override;
            virtual void onMouseFocusLost(Sender s, const MouseEvent& e) override;

            /************************************************************************/
            /* Members                                                              */
            /************************************************************************/
            DrawableRect          m_drawableRect,    m_drawnRect;
            DrawableText          m_drawableText,    m_drawnText;
            vg::GradientType      m_gradBack,        m_gradHover;
            color4                m_backColor1,      m_backColor2;
            color4                m_backHoverColor1, m_backHoverColor2;
            color4                m_textColor,       m_textHoverColor;
            const vg::SpriteFont* m_defaultFont;
        };
    }
}
namespace vui = vorb::ui;

#endif // !Vorb_Button_h__
