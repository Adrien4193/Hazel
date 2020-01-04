#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Utils/Runnable.h"
#include "Hazel/Events/EventListener.h"

namespace Hazel
{
    class OrthographicCameraController : public EventListener, public Runnable
    {
    private:
        const Window &window;
        float aspectRatio = 1.0f;
        float zoomLevel = 1.0f;
        float translationSpeed = 1.0f;
        float rotationSpeed = 90.0f;
        bool rotationEnabled = false;
        OrthographicCamera camera;

    public:
        OrthographicCameraController(const Window &window);

        inline OrthographicCamera &GetCamera()
        {
            return camera;
        }

        inline const OrthographicCamera &GetCamera() const
        {
            return camera;
        }

        inline float GetTranslationSpeed() const
        {
            return translationSpeed;
        }

        inline float GetRotationSpeed() const
        {
            return rotationSpeed;
        }

        inline bool HasRotationEnabled() const
        {
            return rotationEnabled;
        }

        inline void SetTranslationSpeed(float translationSpeed)
        {
            this->translationSpeed = translationSpeed;
        }

        inline void SetRotationSpeed(float rotationSpeed)
        {
            this->rotationSpeed = rotationSpeed;
        }

        inline void SetRotationEnabled(bool rotationEnabled)
        {
            this->rotationEnabled = rotationEnabled;
        }

        virtual void OnUpdate(Timestep deltaTime) override;
        virtual void OnWindowResized(WindowResizedEvent &e) override;
        virtual void OnMouseScrolled(MouseScrolledEvent &e) override;

    private:
        void UpdateCameraPosition(Timestep deltaTime);
        void UpdateCameraRotation(Timestep deltaTime);
        void UpdateCameraViewport();
    };
}