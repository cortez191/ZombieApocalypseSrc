#pragma once

#ifndef		__TEXTURE_H
#define		__TEXTURE_H



// ==============================================
// CTexture_MD2 - texture class object.
// ==============================================

class CTexture_MD2
{
public:
	// constructors/destructor
	CTexture_MD2(void) { }
	CTexture_MD2(const char *texname) { m_name = texname; }
	CTexture_MD2(unsigned int texid, const char *texname) { m_id = texid; m_name = texname; }
	~CTexture_MD2(void) { glDeleteTextures(1, &m_id); m_name.erase(); }

	unsigned int	GetTexId(void) { return m_id; }
	const char		*GetName(void) { return m_name.c_str(); }


public:
	// members variables
	unsigned int	m_id;			// texture id
	std::string		m_name;			// texture name

};



// ==============================================
// CTexture_MD2Manager - OpenGL texture manager.
// ==============================================

class CTexture_MD2Manager
{
protected:
	// constructor/destructor
	CTexture_MD2Manager(void) { Initialize(); }
	virtual ~CTexture_MD2Manager(void) { CleanAllTextures(); }

public:
	// singleton functions
	static CTexture_MD2Manager	*GetInstance(void);
	static void				FreeInstance(void);


	// functions
	void			Initialize(void);
	unsigned int	LoadTexture(const char *filename);
	void			DeleteTexture(unsigned int id);
	void			CleanAllTextures(void);


private:
	// linked texture list
	typedef std::list<CTexture_MD2 *>	TextureList;
	typedef TextureList::iterator	TListItor;

	TextureList						m_texlist;

	// singleton
	static CTexture_MD2Manager			*m_singleton;

};



// global function using the texture manager
inline unsigned int LoadTexture(const char *filename)
{
	return CTexture_MD2Manager::GetInstance()->LoadTexture(filename);
}


#endif	// __TEXTURE_H
