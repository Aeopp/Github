// 버텍스 쉐이더는 정점개수만큼 호출되며 반드시 float4 로 반환해야함
// 정점 쉐이더는 반드시 정점의 위치 SV_POSITION 을 반환해야함

struct POSITION
{
    float3 Pos: POSITION;
};
struct COORD
<<<<<<< HEAD
{
    float2 Coord : TEXCOORD;
};
struct COLOR
{
    float4 Color : COLOR;
};

struct OUT_POSITION
=======
>>>>>>> parent of 7fb459c... Revert "�뀓�뒪泥� �씠誘몄�� �쓣�슦�뒗�뜲源뚯�� 援ы쁽"
{
    float2 Coord : TEXCOORD;
};
<<<<<<< HEAD
struct OUT_TEXCOORD
{
    float2 TexCoord : TEXCOORD0;
};
struct OUT_COLOR
{
    float4 Color : COLOR0;
};

void VS(in POSITION inpos : POSITION,
        in COLOR incolor : COLOR,
        in COORD incoord : TEXCOORD,
        out OUT_POSITION outpos : SV_Position,
        out OUT_COLOR outcolor : COLOR0,
        out OUT_TEXCOORD outtexcoord : TEXCOORD0)
{
    outpos.Pos = float4(inpos.Pos.x, inpos.Pos.y, inpos.Pos.z, 1.f);
    outcolor.Color = incolor.Color;
    outtexcoord.TexCoord = incoord.Coord;
=======
struct OUT_POSITION
{
    float4 Pos : SV_Position;
};
struct OUT_TEXCOORD
{
    float2 TexCoord : TEXCOORD0;
};

void VS(in POSITION pos : POSITION,
        in COORD coord : TEXCOORD,
        out OUT_POSITION outpos : SV_Position,
        out OUT_TEXCOORD texcoord : TEXCOORD0)
{
    outpos.Pos =   float4(pos.Pos.x,pos.Pos.y,pos.Pos.y, 1.f);
    texcoord.TexCoord = coord.Coord;
>>>>>>> parent of 7fb459c... Revert "�뀓�뒪泥� �씠誘몄�� �쓣�슦�뒗�뜲源뚯�� 援ы쁽"
};




