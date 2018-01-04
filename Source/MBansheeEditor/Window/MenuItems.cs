﻿//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Window
     *  @{
     */

    /// <summary>
    /// Contains various menu item callbacks for the main editor menu bar.
    /// </summary>
    static class MenuItems
    {
        /// <summary>
        /// Adds a camera component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Camera", 7050)]
        private static void AddCamera()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Camera component");
            Camera cam = so.AddComponent<Camera>();
            cam.Main = true;

            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a renderable component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Renderable", 7049)]
        private static void AddRenderable()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Renderable component");
            so.AddComponent<Renderable>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a point light component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Radial light", 7048)]
        private static void AddPointLight()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Light component");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Radial;
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a spot light component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Spot light", 7047)]
        private static void AddSpotLight()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Light component");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Spot;
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a directional light component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Directional light", 7046)]
        private static void AddDirectionalLight()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Light component");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Directional;
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a GUI widget component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/GUI widget", 7045)]
        private static void AddGUIWidget()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a GUIWidget component");
            so.AddComponent<GUIWidget>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a BoxCollider component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Box collider", 7044)]
        private static void AddBoxCollider()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            {
                so = UndoRedo.CreateSO("BoxCollider", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a BoxCollider component");
            so.AddComponent<BoxCollider>();

            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a SphereCollider component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Sphere collider", 7043)]
        private static void AddSphereCollider()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("SphereCollider", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a SphereCollider component");
            so.AddComponent<SphereCollider>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a CapsuleCollider component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Capsule collider", 7042)]
        private static void AddCapsuleCollider()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("CapsuleCollider", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a CapsuleCollider component");
            so.AddComponent<CapsuleCollider>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a MeshCollider component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Mesh collider", 7041)]
        private static void AddMeshCollider()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("MeshCollider", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a MeshCollider component");
            so.AddComponent<MeshCollider>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a PlaneCollider component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Plane collider", 7040)]
        private static void AddPlaneCollider()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("PlaneCollider", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a PlaneCollider component");
            so.AddComponent<PlaneCollider>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a Rigidbody component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Rigidbody", 7039, true)]
        private static void AddRigidbody()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            {
                so = UndoRedo.CreateSO("Rigidbody", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a Rigidbody component");
            so.AddComponent<Rigidbody>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a CharacterController component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Character controller", 7038)]
        private static void AddCharacterController()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("CharacterController", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a CharacterController component");
            so.AddComponent<CharacterController>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a FixedJoint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Fixed joint", 7037, true)]
        private static void AddFixedJoint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("FixedJoint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a FixedJoint component");
            so.AddComponent<FixedJoint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a DistanceJoint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Distance joint", 7036)]
        private static void AddDistanceJoint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("DistanceJoint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a DistanceJoint component");
            so.AddComponent<DistanceJoint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a HingeJoint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Hinge joint", 7035)]
        private static void AddHingeJoint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("HingeJoint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a HingeJoint component");
            so.AddComponent<HingeJoint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a SphericalJoint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Spherical joint", 7034)]
        private static void AddSphericalJoint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("SphericalJoint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a SphericalJoint component");
            so.AddComponent<SphericalJoint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a SliderJoint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/Slider joint", 7032)]
        private static void AddSliderJoint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("SliderJoint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a SliderJoint component");
            so.AddComponent<SliderJoint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a D6Joint component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Physics/D6 joint", 7032)]
        private static void AddD6Joint()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            { 
                so = UndoRedo.CreateSO("D6Joint", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a D6Joint component");
            so.AddComponent<D6Joint>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds an AudioListener component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Audio/Listener", 7031)]
        private static void AddAudioListener()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            {
                so = UndoRedo.CreateSO("AudioListener", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a AudioListener component");
            so.AddComponent<AudioListener>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds an AudioSource component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Audio/Source", 7030)]
        private static void AddAudioSource()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
            {
                so = UndoRedo.CreateSO("AudioSource", "New scene object");

                Selection.SceneObject = so;
                FocusOnHierarchyOrScene();
            }

            UndoRedo.RecordSO(so, false, "Added a AudioSource component");
            so.AddComponent<AudioSource>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds an Animation component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Animation", 7029)]
        private static void AddAnimation()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added an Animation component");
            so.AddComponent<Animation>();
            EditorApplication.SetSceneDirty();
        }


        /// <summary>
        /// Adds a Bone component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Bone", 7028)]
        private static void AddBone()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added an Bone component");
            so.AddComponent<Bone>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a Skybox component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Skybox", 7027)]
        private static void AddSkybox()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added an Skybox component");
            so.AddComponent<Skybox>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a ReflectionProbe component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Reflection probe", 7026)]
        private static void AddReflectionProbe()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added an ReflectionProbe component");
            so.AddComponent<ReflectionProbe>();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Adds a LightProbeVolume component to the currently selected scene object.
        /// </summary>
        [MenuItem("Components/Light probe volume", 7025)]
        private static void AddLightProbeVolume()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, false, "Added a Light Probe Volume component");
            so.AddComponent<LightProbeVolume>();
            EditorApplication.SetSceneDirty();
        }


        /// <summary>
        /// Creates a new empty scene object.
        /// </summary>
        [MenuItem("Scene Objects/Scene Object", 8051)]
        [ToolbarItem("SceneObject", ToolbarIcon.NewSceneObject, "Creates a new empty scene object", 1601, true)]
        private static void AddEmptySO()
        {
            SceneObject so = UndoRedo.CreateSO("SceneObject", "New scene object");

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a camera component.
        /// </summary>
        [MenuItem("Scene Objects/Camera", 8050)]
        [ToolbarItem("Camera", ToolbarIcon.NewCamera, "New camera", 1600, false)]
        private static void AddCameraSO()
        {
            SceneObject so = UndoRedo.CreateSO("Camera", "Created a Camera");
            Camera cam = so.AddComponent<Camera>();
            cam.Main = true;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a renderable component.
        /// </summary>
        [MenuItem("Scene Objects/Renderable", 8049)]
        [ToolbarItem("Renderable", ToolbarIcon.NewRenderable, "New renderable", 1599)]
        private static void AddRenderableSO()
        {
            SceneObject so = UndoRedo.CreateSO("Renderable", "Created a Renderable");
            so.AddComponent<Renderable>();

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a point light component.
        /// </summary>
        [MenuItem("Scene Objects/Radial light", 8048)]
        [ToolbarItem("Point light", ToolbarIcon.NewPointLight, "New radial light", 1598)]
        private static void AddPointLightSO()
        {
            SceneObject so = UndoRedo.CreateSO("Radial light", "Created a Light");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Radial;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a spot light component.
        /// </summary>
        [MenuItem("Scene Objects/Spot light", 8047)]
        [ToolbarItem("Spot light", ToolbarIcon.NewSpotLight, "New spot light", 1597)]
        private static void AddSpotLightSO()
        {
            SceneObject so = UndoRedo.CreateSO("Spot light", "Created a Light");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Spot;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a directional light component.
        /// </summary>
        [MenuItem("Scene Objects/Directional light", 8046)]
        [ToolbarItem("Directional light", ToolbarIcon.NewDirLight, "New directional light", 1596)]
        private static void AddDirectionalLightSO()
        {
            SceneObject so = UndoRedo.CreateSO("Directional light", "Created a Light");
            Light light = so.AddComponent<Light>();
            light.Type = LightType.Directional;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a GUI widget component.
        /// </summary>
        [MenuItem("Scene Objects/GUI widget", 8045)]
        private static void AddGUIWidgetSO()
        {
            SceneObject so = UndoRedo.CreateSO("GUIWidget", "Created a GUIWidget");
            so.AddComponent<GUIWidget>();

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a Skybox component.
        /// </summary>
        [MenuItem("Scene Objects/Skybox", 8044)]
        private static void AddSkyboxSO()
        {
            SceneObject so = UndoRedo.CreateSO("Skybox", "Created a Skybox");
            so.AddComponent<Skybox>();

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a ReflectionProbe component.
        /// </summary>
        [MenuItem("Scene Objects/Reflection probe", 8043)]
        private static void AddReflectionProbeSO()
        {
            SceneObject so = UndoRedo.CreateSO("ReflectionProbe", "Created a ReflectionProbe");
            so.AddComponent<ReflectionProbe>();

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a LightProbeVolume component.
        /// </summary>
        [MenuItem("Scene Objects/Light probe volume", 8042)]
        private static void AddLightProbeVolumeSO()
        {
            SceneObject so = UndoRedo.CreateSO("LightProbeVolume", "Created a LightProbeVolume");
            so.AddComponent<LightProbeVolume>();

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a box primitive.
        /// </summary>
        [MenuItem("Scene Objects/3D primitives/Box", 8100)]
        [ToolbarItem("Cube", ToolbarIcon.NewCube, "Creates a scene object with a box primitive", 1700, true)]
        private static void Add3DBox()
        {
            SceneObject so = UndoRedo.CreateSO("Box", "Created a box");
            Renderable renderable = so.AddComponent<Renderable>();
            renderable.Mesh = Builtin.Box;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a sphere primitive.
        /// </summary>
        [MenuItem("Scene Objects/3D primitives/Sphere", 8099)]
        [ToolbarItem("Sphere", ToolbarIcon.NewSphere, "Creates a scene object with a sphere primitive", 1699)]
        private static void Add3DSphere()
        {
            SceneObject so = UndoRedo.CreateSO("Sphere", "Created a sphere");
            Renderable renderable = so.AddComponent<Renderable>();
            renderable.Mesh = Builtin.Sphere;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a cone primitive.
        /// </summary>
        [MenuItem("Scene Objects/3D primitives/Cone", 8098)]
        [ToolbarItem("Cone", ToolbarIcon.NewCone, "Creates a scene object with a cone primitive", 1698)]
        private static void Add3DCone()
        {
            SceneObject so = UndoRedo.CreateSO("Cone", "Created a cone");
            Renderable renderable = so.AddComponent<Renderable>();
            renderable.Mesh = Builtin.Cone;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a quad primitive.
        /// </summary>
        [MenuItem("Scene Objects/3D primitives/Quad", 8097)]
        [ToolbarItem("Quad", ToolbarIcon.NewQuad, "Creates a scene object with a quad primitive", 1697)]
        private static void Add3DQuad()
        {
            SceneObject so = UndoRedo.CreateSO("Quad", "Created a quad");
            Renderable renderable = so.AddComponent<Renderable>();
            renderable.Mesh = Builtin.Quad;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Creates a new scene object with a disc primitive.
        /// </summary>
        [MenuItem("Scene Objects/3D primitives/Disc", 8096)]
        private static void Add3DDisc()
        {
            SceneObject so = UndoRedo.CreateSO("Disc", "Created a disc");
            Renderable renderable = so.AddComponent<Renderable>();
            renderable.Mesh = Builtin.Disc;

            Selection.SceneObject = so;
            FocusOnHierarchyOrScene();
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Applies changes from the prefab instance to the prefab resource.
        /// </summary>
        [MenuItem("Scene Objects/Apply prefab", 8025, true)]
        private static void ApplyPrefab()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            PrefabUtility.ApplyPrefab(so);
        }

        /// <summary>
        /// Reverts a prefab instance to the original state of its prefab.
        /// </summary>
        [MenuItem("Scene Objects/Revert to prefab", 8024)]
        private static void RevertToPrefab()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.RecordSO(so, true, "Reverting \"" + so.Name + "\" to prefab.");

            PrefabUtility.RevertPrefab(so);
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Breaks a link between a prefab and its instance.
        /// </summary>
        [MenuItem("Scene Objects/Break prefab link", 8023)]
        private static void BreakPrefabLink()
        {
            SceneObject so = Selection.SceneObject;
            if (so == null)
                return;

            UndoRedo.BreakPrefab(so, "Breaking prefab link for " + so.Name);
            EditorApplication.SetSceneDirty();
        }

        /// <summary>
        /// Cuts the currently selected scene object or resource.
        /// </summary>
        [MenuItem("Edit/Cut", 9450, true)]
        public static void Cut()
        {
            EditorApplication.TriggerGlobalShortcut(EditorApplication.CutKey);
        }

        /// <summary>
        /// Copies the currently selected scene object or resource.
        /// </summary>
        [MenuItem("Edit/Copy", 9449)]
        public static void Copy()
        {
            EditorApplication.TriggerGlobalShortcut(EditorApplication.CopyKey);
        }

        /// <summary>
        /// Pastes the scene objects or resources that were previously cut or copied.
        /// </summary>
        [MenuItem("Edit/Paste", 9448)]
        public static void Paste()
        {
            EditorApplication.TriggerGlobalShortcut(EditorApplication.PasteKey);
        }

        /// <summary>
        /// Deletes currently selected scene objects or resources.
        /// </summary>
        [MenuItem("Edit/Delete", 9447)]
        public static void Delete()
        {
            EditorApplication.TriggerGlobalShortcut(EditorApplication.DeleteKey);
        }

        /// <summary>
        /// Duplicates currently selected scene objects or resources.
        /// </summary>
        [MenuItem("Edit/Duplicate", 9446)]
        public static void Duplicate()
        {
            EditorApplication.TriggerGlobalShortcut(EditorApplication.DuplicateKey);
        }

        /// <summary>
        /// Executes the last command on the undo stack, undoing its operations.
        /// </summary>
        [MenuItem("Edit/Undo", ButtonModifier.Ctrl, ButtonCode.Z, 9500, true)]
        [ToolbarItem("Undo", ToolbarIcon.Undo, "Undo (Ctrl + Z)", 1900, true)]
        public static void Undo()
        {
            EditorWindow[] allWindows = EditorWindow.AllWindows;
            foreach (var window in allWindows)
            {
                if (!window.HasFocus)
                    continue;

                UndoRedo localStack = window.UndoRedo;
                if (localStack == null)
                    continue;

                localStack.Undo();
                return;
            }

            UndoRedo.Global.Undo();
        }

        /// <summary>
        /// Executes the last command on the redo stack (last command we called undo on), re-applying its operation.
        /// </summary>
        [MenuItem("Edit/Redo", ButtonModifier.Ctrl, ButtonCode.Y, 9499)]
        [ToolbarItem("Redo", ToolbarIcon.Redo, "Redo (Ctrl + Y)", 1899)]
        public static void Redo()
        {
            EditorWindow[] allWindows = EditorWindow.AllWindows;
            foreach (var window in allWindows)
            {
                if (!window.HasFocus)
                    continue;

                UndoRedo localStack = window.UndoRedo;
                if (localStack == null)
                    continue;

                localStack.Redo();
                return;
            }

            UndoRedo.Global.Redo();
        }

        /// <summary>
        /// Sets keyboard focus to the Hierarchy or Scene windows if open.
        /// </summary>
        private static void FocusOnHierarchyOrScene()
        {
            SceneWindow sceneWindow = EditorWindow.GetWindow<SceneWindow>();
            if (sceneWindow != null)
            {
                sceneWindow.HasFocus = true;
                return;
            }

            HierarchyWindow hierarchyWindow = EditorWindow.GetWindow<HierarchyWindow>();
            if (hierarchyWindow != null)
                hierarchyWindow.HasFocus = true;
        }
    }

    /** @} */
}
