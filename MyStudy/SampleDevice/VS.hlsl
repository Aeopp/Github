// ���ؽ� ���̴��� ����������ŭ ȣ��Ǹ� �ݵ�� float4 �� ��ȯ�ؾ���
// ���� ���̴��� �ݵ�� ������ ��ġ SV_POSITION �� ��ȯ�ؾ���

struct POSITION
{
    float3 Pos: POSITION;
};
struct COORD
{
    float2 Coord : TEXCOORD;
};
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
};




