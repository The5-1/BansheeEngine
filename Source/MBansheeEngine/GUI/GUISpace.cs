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
    /// GUI element that may be inserted into layouts in order to make a space of a fixed size.
    /// </summary>
    public sealed class GUIFixedSpace : GUIElement
    {
        /// <summary>
        /// Creates a new fixed space. 
        /// </summary>
        /// <param name="size">Size of the space in pixels. This will represent either width or height depending whether the 
        ///                    layout is vertical or horizontal.</param>
        public GUIFixedSpace(int size)
        {
            Internal_CreateInstance(this, size);
        }

        /// <summary>
        /// Changes the size of the space.
        /// </summary>
        /// <param name="size">Size of the space in pixels. This will represent either width or height depending whether the 
        /// layout is vertical or horizontal.</param>
        public void SetSize(int size)
        {
            Internal_SetSize(mCachedPtr, size);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_CreateInstance(GUIFixedSpace instance, int size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_SetSize(IntPtr nativeInstance, int size);
    }

    /// <summary>
    /// GUI element that may be inserted into layouts to make a space of a flexible size. The space will expand only if there 
    /// is room. If multiple flexible spaces are in a layout, their sizes will be shared equally.
    /// </summary>
    public sealed class GUIFlexibleSpace : GUIElement
    {
        /// <summary>
        /// Creates a new flexible space.
        /// </summary>
        public GUIFlexibleSpace()
        {
            Internal_CreateInstance(this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_CreateInstance(GUIFlexibleSpace instance);
    }

    /** @} */
}
