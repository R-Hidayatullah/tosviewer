#ifndef XAC_FORMATS_H
#define XAC_FORMATS_H
#include "shared_formats.h"

// collection of XAC chunk IDs
enum
{
	XAC_CHUNK_NODE = 0,
	XAC_CHUNK_MESH = 1,
	XAC_CHUNK_SKINNINGINFO = 2,
	XAC_CHUNK_STDMATERIAL = 3,
	XAC_CHUNK_STDMATERIALLAYER = 4,
	XAC_CHUNK_FXMATERIAL = 5,
	XAC_CHUNK_LIMIT = 6,
	XAC_CHUNK_INFO = 7,
	XAC_CHUNK_MESHLODLEVELS = 8,
	XAC_CHUNK_STDPROGMORPHTARGET = 9,
	XAC_CHUNK_NODEGROUPS = 10,
	XAC_CHUNK_NODES = 11,			// XAC_Nodes
	XAC_CHUNK_STDPMORPHTARGETS = 12,			// XAC_PMorphTargets
	XAC_CHUNK_MATERIALINFO = 13,			// XAC_MaterialInfo
	XAC_CHUNK_NODEMOTIONSOURCES = 14,			// XAC_NodeMotionSources
	XAC_CHUNK_ATTACHMENTNODES = 15,			// XAC_AttachmentNodes
	XAC_FORCE_32BIT = 0xFFFFFFFF
};


// material layer map types
enum
{
	XAC_LAYERID_UNKNOWN = 0,	// unknown layer
	XAC_LAYERID_AMBIENT = 1,	// ambient layer
	XAC_LAYERID_DIFFUSE = 2,	// a diffuse layer
	XAC_LAYERID_SPECULAR = 3,	// specular layer
	XAC_LAYERID_OPACITY = 4,	// opacity layer
	XAC_LAYERID_BUMP = 5,	// bump layer
	XAC_LAYERID_SELFILLUM = 6,	// self illumination layer
	XAC_LAYERID_SHINE = 7,	// shininess (for specular)
	XAC_LAYERID_SHINESTRENGTH = 8,	// shine strength (for specular)
	XAC_LAYERID_FILTERCOLOR = 9,	// filter color layer
	XAC_LAYERID_REFLECT = 10,	// reflection layer
	XAC_LAYERID_REFRACT = 11,	// refraction layer
	XAC_LAYERID_ENVIRONMENT = 12, 	// environment map layer
	XAC_LAYERID_DISPLACEMENT = 13, 	// displacement map layer
	XAC_LAYERID_FORCE_8BIT = 0xFF	// don't use more than 8 bit values
};


// the actor file type header
struct XAC_Header
{
	uint8_t mFourcc[4];		// must be "XAC "
	uint8_t mHiVersion;		// high version (2  in case of v2.34)
	uint8_t mLoVersion;		// low version  (34 in case of v2.34)
	uint8_t mEndianType;		// the endian in which the data is saved [0=little, 1=big]
	uint8_t mMulOrder;		// see the enum MULORDER_....
};


//
struct XAC_Info
{
	uint32_t	mRepositioningMask;			// the repositioning mask, which describes what transformation components to adjust when repositioning is enabled
	uint32_t	mRepositioningNodeIndex;	// the node number
	uint8_t	mExporterHighVersion;
	uint8_t	mExporterLowVersion;

	// followed by:
	// string : source application (e.g. "3D Studio MAX 8", "Maya 7.0")
	// string : original filename of the 3dsMax/Maya file
	// string : compilation date of the exporter
	// string : the name of the actor
};


//
struct XAC_Info2
{
	uint32_t	mRepositioningMask;			// the repositioning mask, which describes what transformation components to adjust when repositioning is enabled
	uint32_t	mRepositioningNodeIndex;	// the node number
	uint8_t	mExporterHighVersion;
	uint8_t	mExporterLowVersion;
	float	mRetargetRootOffset;

	// followed by:
	// string : source application (e.g. "3D Studio MAX 8", "Maya 7.0")
	// string : original filename of the 3dsMax/Maya file
	// string : compilation date of the exporter
	// string : the name of the actor
};


//
struct XAC_Info3
{
	uint32_t	mTrajectoryNodeIndex;		// the node number of the trajectory node used for motion extraction
	uint32_t	mMotionExtractionNodeIndex;	// the node number of the trajectory node used for motion extraction
	uint32_t	mMotionExtractionMask;		// the motion extraction mask, which describes what transformation components to adjust when motion extraction is enabled
	uint8_t	mExporterHighVersion;
	uint8_t	mExporterLowVersion;
	float	mRetargetRootOffset;

	// followed by:
	// string : source application (e.g. "3ds Max 2011", "Maya 2011")
	// string : original filename of the 3dsMax/Maya file
	// string : compilation date of the exporter
	// string : the name of the actor
};


//
struct XAC_Info4
{
	uint32_t	mNumLODs;					// the number of level of details
	uint32_t	mTrajectoryNodeIndex;		// the node number of the trajectory node used for motion extraction
	uint32_t	mMotionExtractionNodeIndex;	// the node number of the trajectory node used for motion extraction
	uint8_t	mExporterHighVersion;
	uint8_t	mExporterLowVersion;
	float	mRetargetRootOffset;

	// followed by:
	// string : source application (e.g. "3ds Max 2011", "Maya 2011")
	// string : original filename of the 3dsMax/Maya file
	// string : compilation date of the exporter
	// string : the name of the actor
};



// a node header
struct XAC_Node
{
	FileQuaternion	mLocalQuat;		// the local rotation (before hierarchy)
	FileQuaternion	mScaleRot;		// scale rotation (space in which to perform scaling)
	FileVector3		mLocalPos;		// the local translation (before hierarchy)
	FileVector3		mLocalScale;	// the local scale (before hierarchy)
	FileVector3		mShear;			// shear (x=XY, y=XZ, z=YZ)
	uint32_t			mSkeletalLODs;	// each bit representing if the node is active or not, in the give LOD (bit number)
	uint32_t			mParentIndex;	// parent node number, or 0xFFFFFFFF in case of a root node

	// followed by:
	// string : node name (the unique name of the node)
};

// a node header
struct XAC_Node2
{
	FileQuaternion	mLocalQuat;		// the local rotation (before hierarchy)
	FileQuaternion	mScaleRot;		// scale rotation (space in which to perform scaling)
	FileVector3		mLocalPos;		// the local translation (before hierarchy)
	FileVector3		mLocalScale;	// the local scale (before hierarchy)
	FileVector3		mShear;			// shear (x=XY, y=XZ, z=YZ)
	uint32_t			mSkeletalLODs;	// each bit representing if the node is active or not, in the give LOD (bit number)
	uint32_t			mParentIndex;	// parent node number, or 0xFFFFFFFF in case of a root node
	uint8_t			mNodeFlags;		// #1 bit boolean specifies whether we have to include this node in the bounds calculation or not

	// followed by:
	// string : node name (the unique name of the node)
};

// a node header
struct XAC_Node3
{
	FileQuaternion	mLocalQuat;		// the local rotation (before hierarchy)
	FileQuaternion	mScaleRot;		// scale rotation (space in which to perform scaling)
	FileVector3		mLocalPos;		// the local translation (before hierarchy)
	FileVector3		mLocalScale;	// the local scale (before hierarchy)
	FileVector3		mShear;			// shear (x=XY, y=XZ, z=YZ)
	uint32_t			mSkeletalLODs;	// each bit representing if the node is active or not, in the give LOD (bit number)
	uint32_t			mParentIndex;	// parent node number, or 0xFFFFFFFF in case of a root node
	uint8_t			mNodeFlags;		// #1 bit boolean specifies whether we have to include this node in the bounds calculation or not
	float			mOBB[16];

	// followed by:
	// string : node name (the unique name of the node)
};

// a node header
struct XAC_Node4
{
	FileQuaternion	mLocalQuat;		// the local rotation (before hierarchy)
	FileQuaternion	mScaleRot;		// scale rotation (space in which to perform scaling)
	FileVector3		mLocalPos;		// the local translation (before hierarchy)
	FileVector3		mLocalScale;	// the local scale (before hierarchy)
	FileVector3		mShear;			// shear (x=XY, y=XZ, z=YZ)
	uint32_t			mSkeletalLODs;	// each bit representing if the node is active or not, in the give LOD (bit number)
	uint32_t			mMotionLODs;	// each bit representing if the node is active or not, in the give LOD (bit number)
	uint32_t			mParentIndex;	// parent node number, or 0xFFFFFFFF in case of a root node
	uint32_t			mNumChilds;		// the number of child nodes
	uint8_t			mNodeFlags;		// #1 bit boolean specifies whether we have to include this node in the bounds calculation or not
	float			mOBB[16];
	float			mImportanceFactor; // importance factor used for the automatic motion lod

	// followed by:
	// string : node name (the unique name of the node)
};

// a mesh LOD level
struct XAC_MeshLODLevel
{
	uint32_t mLODLevel;
	uint32_t mSizeInBytes;

	// followed by:
	// array[uint8_t] The LOD model memory file
};


// uv (texture) coordinate
struct XAC_UV
{
	float	mU;
	float	mV;
};


struct XAC_SkinningInfo
{
	uint32_t	mNodeIndex;
	uint8_t	mIsForCollisionMesh;

	// followed by:
	// for all mesh org num vertices
	//     uint8_t numInfluences
	//         XAC_SkinInfluence[numInfluences];
};

struct XAC_SkinningInfo2
{
	uint32_t	mNodeIndex;					// the node number in the actor
	uint32_t	mNumTotalInfluences;		// the total number of influences of all vertices together
	uint8_t	mIsForCollisionMesh;		// is it for a collision mesh?

	// followed by:
	//	 XAC_SkinInfluence[mNumTotalInfluences]
	//	 XAC_SkinningInfoTableEntry[mesh.GetNumOrgVerts()]
};

struct XAC_SkinningInfo3
{
	uint32_t	mNodeIndex;					// the node number in the actor
	uint32_t	mNumLocalBones;				// number of local bones to reserve space for, this represents how many bones are used by the mesh the skinning is linked to
	uint32_t	mNumTotalInfluences;		// the total number of influences of all vertices together
	uint8_t	mIsForCollisionMesh;		// is it for a collision mesh?

	// followed by:
	//	 XAC_SkinInfluence[mNumTotalInfluences]
	//	 XAC_SkinningInfoTableEntry[mesh.GetNumOrgVerts()]
};

struct XAC_SkinningInfo4
{
	uint32_t	mNodeIndex;					// the node number in the actor
	uint32_t	mLOD;						// the level of detail
	uint32_t	mNumLocalBones;				// number of local bones to reserve space for, this represents how many bones are used by the mesh the skinning is linked to
	uint32_t	mNumTotalInfluences;		// the total number of influences of all vertices together
	uint8_t	mIsForCollisionMesh;		// is it for a collision mesh?

	// followed by:
	//	 XAC_SkinInfluence[mNumTotalInfluences]
	//	 XAC_SkinningInfoTableEntry[mesh.GetNumOrgVerts()]
};

struct XAC_SkinningInfoTableEntry
{
	uint32_t	mStartIndex;	// index inside the SkinInfluence array
	uint32_t	mNumElements;	// the number of influences for this item/entry that follow from the given start index
};


// a skinning influence
struct XAC_SkinInfluence
{
	float	mWeight;
	uint16_t	mNodeNr;
};


// standard material
struct XAC_StandardMaterial
{
	FileColor	mAmbient;			// ambient color
	FileColor	mDiffuse;			// diffuse color
	FileColor	mSpecular;			// specular color
	FileColor	mEmissive;			// self illumination color
	float		mShine;				// shine
	float		mShineStrength;		// shine strength
	float		mOpacity;			// the opacity amount [1.0=full opac, 0.0=full transparent]
	float		mIOR;				// index of refraction
	uint8_t		mDoubleSided;		// double sided?
	uint8_t		mWireFrame;			// render in wireframe?
	uint8_t		mTransparencyType;	// F=filter / S=substractive / A=additive / U=unknown

	// followed by:
	// string : material name
};


// standard material, with integrated set of standard material layers
struct XAC_StandardMaterial2
{
	FileColor	mAmbient;			// ambient color
	FileColor	mDiffuse;			// diffuse color
	FileColor	mSpecular;			// specular color
	FileColor	mEmissive;			// self illumination color
	float		mShine;				// shine
	float		mShineStrength;		// shine strength
	float		mOpacity;			// the opacity amount [1.0=full opac, 0.0=full transparent]
	float		mIOR;				// index of refraction
	uint8_t		mDoubleSided;		// double sided?
	uint8_t		mWireFrame;			// render in wireframe?
	uint8_t		mTransparencyType;	// F=filter / S=substractive / A=additive / U=unknown
	uint8_t		mNumLayers;			// the number of material layers

	// followed by:
	// string : material name
	// XAC_StandardMaterialLayer2[ mNumLayers ]
};

// standard material, with integrated set of standard material layers
struct XAC_StandardMaterial3
{
	uint32_t		mLOD;				// the level of detail
	FileColor	mAmbient;			// ambient color
	FileColor	mDiffuse;			// diffuse color
	FileColor	mSpecular;			// specular color
	FileColor	mEmissive;			// self illumination color
	float		mShine;				// shine
	float		mShineStrength;		// shine strength
	float		mOpacity;			// the opacity amount [1.0=full opac, 0.0=full transparent]
	float		mIOR;				// index of refraction
	uint8_t		mDoubleSided;		// double sided?
	uint8_t		mWireFrame;			// render in wireframe?
	uint8_t		mTransparencyType;	// F=filter / S=substractive / A=additive / U=unknown
	uint8_t		mNumLayers;			// the number of material layers

	// followed by:
	// string : material name
	// XAC_StandardMaterialLayer2[ mNumLayers ]
};

// a material layer
struct XAC_StandardMaterialLayer
{
	float	mAmount;			// the amount, between 0 and 1
	float	mUOffset;			// u offset (horizontal texture shift)
	float	mVOffset;			// v offset (vertical texture shift)
	float	mUTiling;			// horizontal tiling factor
	float	mVTiling;			// vertical tiling factor
	float	mRotationRadians;	// texture rotation in radians
	uint16_t	mMaterialNumber;	// the parent material number (as read from the file, where 0 means the first material)
	uint8_t	mMapType;			// the map type (see enum in somewhere near the top of file)

	// followed by:
	// string : texture filename
};

// a material layer (version 2)
struct XAC_StandardMaterialLayer2
{
	float	mAmount;			// the amount, between 0 and 1
	float	mUOffset;			// u offset (horizontal texture shift)
	float	mVOffset;			// v offset (vertical texture shift)
	float	mUTiling;			// horizontal tiling factor
	float	mVTiling;			// vertical tiling factor
	float	mRotationRadians;	// texture rotation in radians
	uint16_t	mMaterialNumber;	// the parent material number (as read from the file, where 0 means the first material)
	uint8_t	mMapType;			// the map type (see enum in somewhere near the top of file)
	uint8_t	mBlendMode;			// blend mode that is used to control how successive layers of textures are combined together

	// followed by:
	// string : texture filename
};


//-------------------------------------------------------
// a vertex attribute layer
struct XAC_VertexAttributeLayer
{
	uint32_t	mLayerTypeID;		// the type of vertex attribute layer
	uint32_t	mAttribSizeInBytes;	// the size of a single vertex attribute of this type, in bytes
	uint8_t	mEnableDeformations;// enable deformations on this layer?
	uint8_t	mIsScale;			// is this a scale value, or not? (coordinate system conversion thing)

	// followed by:
	// (sizeof(mAttribSizeInBytes) * mesh.numVertices) bytes, or mesh.numVertices mDataType objects
};


// a submesh
struct XAC_SubMesh
{
	uint32_t	mNumIndices;		// number of indices
	uint32_t	mNumVerts;			// number of vertices
	uint32_t	mMaterialIndex;		// material number, indexes into the file, so 0 means the first read material
	uint32_t	mNumBones;			// the number of bones used by this submesh

	// followed by:
	// uint32_t[mNumIndices]
	// uint32_t[mNumBones]
};


// a mesh
struct XAC_Mesh
{
	uint32_t	mNodeIndex;			// the node number this mesh belongs to (0 means the first node in the file, 1 means the second, etc.)
	uint32_t	mNumOrgVerts;		// number of original vertices
	uint32_t	mTotalVerts;		// total number of vertices (of all submeshes)
	uint32_t	mTotalIndices;		// total number of indices (of all submeshes)
	uint32_t	mNumSubMeshes;		// number of submeshes to follow
	uint32_t	mNumLayers;			// the number of layers to follow
	uint8_t	mIsCollisionMesh;	// is this mesh a collision mesh or a normal mesh?

	// followed by:
	// XAC_VertexAttributeLayer[mNumLayers]
	// XAC_SubMesh[mNumSubMeshes]
};

// a mesh
struct XAC_Mesh2
{
	uint32_t	mNodeIndex;			// the node number this mesh belongs to (0 means the first node in the file, 1 means the second, etc.)
	uint32_t	mLOD;				// the level of detail
	uint32_t	mNumOrgVerts;		// number of original vertices
	uint32_t	mTotalVerts;		// total number of vertices (of all submeshes)
	uint32_t	mTotalIndices;		// total number of indices (of all submeshes)
	uint32_t	mNumSubMeshes;		// number of submeshes to follow
	uint32_t	mNumLayers;			// the number of layers to follow
	uint8_t	mIsCollisionMesh;	// is this mesh a collision mesh or a normal mesh?

	// followed by:
	// XAC_VertexAttributeLayer[mNumLayers]
	// XAC_SubMesh[mNumSubMeshes]
};

//-------------------------------------------------------


// node limit information
struct XAC_Limit
{
	FileVector3		mTranslationMin;	// the minimum translation values
	FileVector3		mTranslationMax;	// the maximum translation value.
	FileVector3		mRotationMin;		// the minimum rotation values
	FileVector3		mRotationMax;		// the maximum rotation values
	FileVector3		mScaleMin;			// the minimum scale values
	FileVector3		mScaleMax;			// the maximum scale values
	uint8_t			mLimitFlags[9];		// the limit type activation flags
	uint32_t			mNodeNumber;		// the node number where this info belongs to
};


// a progressive morph target mesh
struct XAC_PMorphTarget
{
	float	mRangeMin;				// the slider min
	float	mRangeMax;				// the slider max
	uint32_t	mLOD;					// the level of detail to which this expression part belongs to
	uint32_t	mNumMeshDeformDeltas;	// the number of mesh deform data objects to follow
	uint32_t	mNumTransformations;	// the number of transformations to follow
	uint32_t	mPhonemeSets;			// the number of phoneme sets to follow

	// followed by:
	// string : progressive morph target name
	// XAC_PMorphTargetMeshDeltas[ mNumDeformDatas ]
	// XAC_PMorphTargetTransform[ mNumTransformations ]
};


// a chunk that contains all morph targets in the file
struct XAC_PMorphTargets
{
	uint32_t	mNumMorphTargets;		// the number of morph targets to follow
	uint32_t	mLOD;					// the LOD level the morph targets are for

	// followed by:
	// XAC_PMorphTarget[ mNumMorphTargets ]
};


// morph target deformation data
struct XAC_PMorphTargetMeshDeltas
{
	uint32_t	mNodeIndex;
	float	mMinValue;			// minimum range value for x y and z components of the compressed position vectors
	float	mMaxValue;			// maximum range value for x y and z components of the compressed position vectors
	uint32_t	mNumVertices;		// the number of deltas

	// followed by:
	// File16BitVector3[ mNumVertices ]  (delta position values)
	// File8BitVector3[ mNumVertices ]	 (delta normal values)
	// File8BitVector3[ mNumVertices ]	 (delta tangent values)
	// uint32_t[ mNumVertices ]			 (vertex numbers)
};


// a progressive morph target transformation
struct XAC_PMorphTargetTransform
{
	uint32_t			mNodeIndex;				// the node name where the transform belongs to
	FileQuaternion	mRotation;				// the node rotation
	FileQuaternion	mScaleRotation;			// the node delta scale rotation
	FileVector3		mPosition;				// the node delta position
	FileVector3		mScale;					// the node delta scale
};

// an FX material, using parameters
struct XAC_FXMaterial
{
	uint32_t mNumIntParams;
	uint32_t mNumFloatParams;
	uint32_t mNumColorParams;
	uint32_t mNumBitmapParams;

	// followed by:
	// string : name
	// string : effect file (path excluded, extension included)
	// XAC_FXIntParameter   [ mNumIntParams ]
	// XAC_FXFloatParameter [ mNumFloatParams ]
	// XAC_FXColorParameter [ mNumColorParams ]
	// [mNumBitmapParams]
	//		string : param name
	//		string : value
};

// an FX material, using parameters
struct XAC_FXMaterial2
{
	uint32_t mNumIntParams;
	uint32_t mNumFloatParams;
	uint32_t mNumColorParams;
	uint32_t mNumBoolParams;
	uint32_t mNumVector3Params;
	uint32_t mNumBitmapParams;

	// followed by:
	// string : name
	// string : effect file (path excluded, extension included)
	// string : shader technique
	// XAC_FXIntParameter		[ mNumIntParams ]
	// XAC_FXFloatParameter		[ mNumFloatParams ]
	// XAC_FXColorParameter		[ mNumColorParams ]
	// XAC_FXBoolParameter		[ mNumBoolParams ]
	// XAC_FXVector3Parameter	[ mNumVector3Params ]
	// [mNumBitmapParams]
	//		string : param name
	//		string : value
};

// an FX material, using parameters
struct XAC_FXMaterial3
{
	uint32_t mLOD;				// the level of detail
	uint32_t mNumIntParams;
	uint32_t mNumFloatParams;
	uint32_t mNumColorParams;
	uint32_t mNumBoolParams;
	uint32_t mNumVector3Params;
	uint32_t mNumBitmapParams;

	// followed by:
	// string : name
	// string : effect file (path excluded, extension included)
	// string : shader technique
	// XAC_FXIntParameter		[ mNumIntParams ]
	// XAC_FXFloatParameter		[ mNumFloatParams ]
	// XAC_FXColorParameter		[ mNumColorParams ]
	// XAC_FXBoolParameter		[ mNumBoolParams ]
	// XAC_FXVector3Parameter	[ mNumVector3Params ]
	// [mNumBitmapParams]
	//		string : param name
	//		string : value
};

struct XAC_FXIntParameter
{
	int32_t	mValue;		// beware, not unsigned, as negative would also be allowed
	// followed by:
	// string : name
};


struct XAC_FXFloatParameter
{
	float mValue;
	// followed by:
	// string : name
};


struct XAC_FXColorParameter
{
	FileColor mValue;
	// followed by:
	// string : name
};


struct XAC_FXVector3Parameter
{
	FileVector3 mValue;
	// followed by:
	// string : name
};


struct XAC_FXBoolParameter
{
	uint8_t mValue;					// 0 = no, 1 = yes
	// followed by:
	// string : name
};


// a node group
struct XAC_NodeGroup
{
	uint16_t	mNumNodes;
	uint8_t	mDisabledOnDefault;		// 0 = no, 1 = yes

	// followed by:
	// string : name
	// uint16_t [mNumNodes]
};


// a collection of all nodes
struct XAC_Nodes
{
	uint32_t	mNumNodes;
	uint32_t	mNumRootNodes;
	// followed by XAC_Node4[mNumNodes]
};


// material statistics, which appears before the actual material chunks
struct XAC_MaterialInfo
{
	uint32_t	mNumTotalMaterials;			// total number of materials to follow (including default/extra material)
	uint32_t	mNumStandardMaterials;		// the number of standard materials in the file
	uint32_t	mNumFXMaterials;			// the number of fx materials in the file
};

// material statistics, which appears before the actual material chunks
struct XAC_MaterialInfo2
{
	uint32_t	mLOD;						// the level of detail
	uint32_t	mNumTotalMaterials;			// total number of materials to follow (including default/extra material)
	uint32_t	mNumStandardMaterials;		// the number of standard materials in the file
	uint32_t	mNumFXMaterials;			// the number of fx materials in the file
};

// node motion sources used for the motion mirroring feature
struct XAC_NodeMotionSources
{
	uint32_t mNumNodes;
	// followed by uint16_t[mNumNodes]	// an index per node, which indicates the index of the node to extract the motion data from in case mirroring for a given motion is enabled. This array can be NULL in case no mirroring data has been setup.
};

// list of node number which are used for attachments
struct XAC_AttachmentNodes
{
	uint32_t mNumNodes;
	// followed by uint16_t[mNumNodes]	// an index per attachment node
};

#endif // !XAC_FORMATS_H
