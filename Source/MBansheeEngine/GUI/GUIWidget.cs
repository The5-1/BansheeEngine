﻿//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
namespace BansheeEngine
{
    /** @addtogroup GUI_Engine
     *  @{
     */

    /// <summary>
    /// Container of GUI elements that can be positioned in the scene, and can output the rendered GUI to a user defined
    /// camera.
    /// </summary>
    public class GUIWidget : ManagedComponent
    {
        private NativeGUIWidget nativeGUIWidget;

        [SerializeField]
        private SerializableData serializableData = new SerializableData();

        /// <summary>
        /// Skin used for rendering all the GUI elements belonging to this widget.
        /// </summary>
        public GUISkin Skin
        {
            get { return serializableData.skin; }
            set
            {
                serializableData.skin = value;
                nativeGUIWidget.Skin = value;
            }
        }

        /// <summary>
        /// Determines to which camera are the GUI elements belonong to this widget rendered. If null then they will be
        /// rendered on the main camera.
        /// </summary>
        public Camera Camera
        {
            get { return serializableData.camera; }
            set
            {
                serializableData.camera = value;
                nativeGUIWidget.Camera = value;
            }
        }

        /// <summary>
        /// Container into which all GUI elements belonging to this widget should be placed.
        /// </summary>
        public GUIPanel Panel
        {
            get { return nativeGUIWidget.Panel; }
        }

        /// <summary>
        /// Depth that determines in which order are GUI widgets rendered. Widgets with lower depth are rendered in front
        /// of widgets with higher depth.
        /// </summary>
        public short Depth
        {
            set { nativeGUIWidget.Depth = value; }
            get { return nativeGUIWidget.Depth; }
        }

        private void OnReset()
        {
            if (nativeGUIWidget != null)
                nativeGUIWidget.Destroy();

            nativeGUIWidget = new NativeGUIWidget();

            // Restore saved values after reset
            nativeGUIWidget.Skin = serializableData.skin;
            nativeGUIWidget.Camera = serializableData.camera;
        }

        private void OnUpdate()
        {
            nativeGUIWidget.UpdateTransform(SceneObject);

            if (serializableData.camera == null)
                nativeGUIWidget.UpdateMainCamera(Scene.Camera);
        }

        private void OnDestroy()
        {
            nativeGUIWidget.Destroy();
        }

        /// <summary>
        /// Holds all data the GUIWidget component needs to persist through serialization.
        /// </summary>
        [SerializeObject]
        private class SerializableData
        {
            public GUISkin skin;
            public Camera camera;
        }
    }

    /** @} */
}
