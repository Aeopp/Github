Texture2D TEXTURE2D : register(t0);
SamplerState SAMPLERSTATE : register(s0);

struct POSITION
{
    float4 Pos : SV_Position;
};
struct COORD 
{
    float2 Coord : TEXCOORD0;
};
<<<<<<< HEAD
struct COLOR
{
    float4 COLOR : COLOR0;
};
    struct TARGET
=======
struct TARGET
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
{
    float4 Target : SV_Target;
};

void PS(in POSITION pos : SV_Position,
<<<<<<< HEAD
        in COLOR color : COLOR0,
        in COORD texcoord : TEXCOORD0,
        out TARGET target: SV_Target)
{
    float4 color1 = TEXTURE2D.Sample(SAMPLERSTATE, texcoord.Coord);
    
    if (color1.r >= 1.f &&
        color1.g <= 0.f &&
        color1.b >= 1.f)        discard;
    
    target.Target = color1 * color.COLOR;
=======
        in COORD texcoord : TEXCOORD0,
        out TARGET target: SV_Target)
{
    target.Target = TEXTURE2D.Sample(SAMPLERSTATE, texcoord.Coord);
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
}