namespace Helium;

[NativePath("Helium/CoreGame/Camera")]
public class Camera : ActorComponent
{
    public CameraType CameraType { get; set; }
    public mat4 ProjectionMatrix { get; }
    public mat4 ViewMatrix { get; }
    public F32 FOV { get; set; }
    public F32 NearPlane { get; set; }
    public F32 FarPlane { get; set; }
    public F32 AspectRatio { get; set; }
}
