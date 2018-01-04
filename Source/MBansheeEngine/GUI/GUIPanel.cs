﻿//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using System.Runtime.CompilerServices;

namespace BansheeEngine
{
    /** @addtogroup GUI_Engine
     *  @{
     */

    /// <summary>
    /// Represents a GUI panel that you can use for free placement of GUI elements within its bounds.
    /// </summary>
    public sealed class GUIPanel : GUILayout
    {
        private GUIPanel()
        { }

        /// <summary>
        /// Constructs a new GUI panel object.
        /// </summary>
        /// <param name="depth">Depth at which to position the panel. Panels with lower depth will be displayed in front of 
        ///                     panels with higher depth. Provided depth is relative to the depth of the parent GUI panel. 
        ///                     The depth value will be clamped if outside of the depth range of the parent GUI panel.</param>
        /// <param name="depthRangeMin">Smallest depth offset allowed by any child GUI panels. If a child panel has a depth 
        ///                             offset lower than this value it will be clamped.</param>
        /// <param name="depthRangeMax">Largest depth offset allowed by any child GUI panels. If a child panel has a depth 
        ///                             offset higher than this value it will be clamped.</param>
        /// <param name="options">Options that allow you to control how is the panel positioned and sized.</param>
        public GUIPanel(Int16 depth = 0, ushort depthRangeMin = ushort.MaxValue, ushort depthRangeMax = ushort.MaxValue, 
            params GUIOption[] options)
        {
            Internal_CreateInstancePanel(this, depth, depthRangeMin, depthRangeMax, options);
        }

        /// <summary>
        /// Constructs a new GUI panel object.
        /// </summary>
        /// <param name="options">Options that allow you to control how is the panel positioned and sized.</param>
        public GUIPanel(params GUIOption[] options)
        {
            Internal_CreateInstancePanel(this, 0, ushort.MaxValue, ushort.MaxValue, options);
        }
    }

    /** @} */
}
