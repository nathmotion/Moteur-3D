/**
 * @author     G.Gilet, Guillaume.Gilet@unilim.fr
 * @date       October 8, 2012
 * @version    1.0 (alpha)
 */

#ifndef __FRAME__
#define __FRAME__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
/**
 * @brief      Class defining a 3D frame
 *
 * @details    TO DO : Usage scenario
 *
 */



class Frame
{
public:

	/**
	 * @brief      Creates a new Frame.
	 */
	Frame();
	/**
	 * @brief      Destroy a Frame.
	 */
	~Frame();

	/**
	 * @brief      Load identity matrix into frame matrix.
	 */
	void loadIdentity();

	/**
	 * @brief Define frame matrix using a given matrix .
	 *
	 * @param m the new frame matrix
	 */
	void setUpFromMatrix(const glm::mat4 & m);

	/**
	 * @brief Get pointer to frame matrix
	 * @return pointer to frame matrix
	 **/
	glm::mat4* getMatrix(){ return(&matrix); };

	glm::mat4 getMatrixCopy();

	/**
	 * @brief Get complete chain of matrix transformation
	 * @details Frame are chained together, usually mirroring the scene graph. This function return the complete transformation matrix from this frame to the frame on top of chain, usually the projection frame of a Camera. Thus this function returns the MVP matrix used to define transformation from this frame to camera clip space. It can be formally defined as father.getTransformMatrix() * frame.matrix.
	 * @see Camera
	 * @return transformation matrix to the top of chained frame
	 **/
	glm::mat4 getTransformMatrix();

	/**
	 * @brief Get chain of matrix transformation to root node
	 * @details Get matrix of transformation from this frame to the top node of the frame chain, ignoring camera related transformation. It is basically a transformation to "world space"
	 * @return transformation matrix to the top of chained frame, ignoring camera related frame
	 **/
	glm::mat4 getRootMatrix();

	/**
	 * @brief Attach this frame to another frame. This frame is therefore defined relative to frame $f$.
	 * @param f as parent frame
	 **/
	void attachTo(Frame *f);

	/**
	* @brief Detach a frame from the current frame.
	* @param f as child frame
	**/
	bool detach(Frame* f);


	/*
	 *
	 * Transformations g�ometriques
	 *
	 */


	/**
	 * @brief Perform a rotation around axis of angle degrees
	 *@param axis for axis of rotation
	 *@param angle for angle of rotation in degrees
	 **/
	void rotate(glm::vec3 axis, float angle);
	/**
	 * @brief Perform a translation of vector v
	 * @param v vector of translation
	 **/
	void translate(glm::vec3 V);
	/**
	 * @brief Perform a scale of vector size
	 * @details Basically multiply each coordinates by vector size (1.0 is our neutral element)
	 * @param size vector of scaling
	 **/
	void scale(glm::vec3 size);

	/**
	 * @brief Convert coordinates of a 3D point pt expressed in frame fSource to coordinates expressed in this frame.
	 *
	 * @param pt for point coordinates (expressed in fSource frame).
	 * @param fSource as source frame.
	 * @return coordinates of point pt in this frame.
	 * @warning frame fSource and this frame must be linked in the scene graph (there must be a path of conversion between f and current frame) for success of conversion operation. Results of conversion between unlinked frames are undefined
	 **/

	glm::vec3 convertPtFrom(glm::vec3 pt, Frame *from);
	/**
	 * @brief Convert coordinates of a 3D direction dir expressed in frame fSource to coordinates expressed in this frame.
	 *
	 * @param dir for direction coordinates (expressed in fSource frame).
	 * @param fSource as source frame.
	 * @return coordinates of direction dir in the current frame.
	 * @warning frame fSource and current frame must be linked in the scene graph (there must be a path of conversion between f and this frame) for success of conversion operation. Results of conversion between unlinked frames are undefined
	 **/
	glm::vec3 convertDirFrom(glm::vec3 dir, Frame *from);
	/**
	 * @brief Convert coordinates of a 3D point pt expressed in this frame to coordinates expressed in frame fDest.
	 *
	 * @param pt for point coordinates (expressed in this frame).
	 * @param fDest as destination frame.
	 * @return coordinates of point pt in the frame f.
	 * @warning frame fDest and current frame must be linked in the scene graph (there must be a path of conversion between f and this frame) for success of conversion operation. Results of conversion between unlinked frames are undefined
	 **/
	glm::vec3 convertPtTo(glm::vec3 pt, Frame *to);
	/**
	 * @brief Convert coordinates of a 3D direction dir expressed in current Frame to coordinates expressed in frame fDest.
	 *
	 * @param dir for direction coordinates (expressed in this frame).
	 * @param fDest as destination frame.
	 * @return coordinates of direction dir in the frame f.
	 * @warning frame fDest and this frame must be linked in the scene graph (there must be a path of conversion between fDest and current frame) for success of conversion operation. Results of conversion between unlinked frames are undefined
	 **/
	glm::vec3 convertDirTo(glm::vec3 dir, Frame *to);
	/**
	 * @brief Returns position in clipped screen space of point pos defined in this frame.
	 *
	 * @param pos coordinates of point (expressed in this frame).
	 * @return position of pos projected in clipped screen space.
	 * @warning This frame must be linked in the scene graph to a valid camera frame (there must be a path of conversion between camera and current frame) for success of conversion operation. Results of conversion between unlinked frames are undefined
	 **/

	glm::vec3 getScreenPosition(glm::vec3 pos = glm::vec3(0.0));

	/**
	 * @brief Convenience function. Return true if current frame is belonging to a valid instance of Camera class.
	 *@return true if current frame is frame belonging to Camera class.
	 **/

	bool isCameraFrame();
	/**
	 * @brief Convenience function. Flag current frame as belonging to an instance of Camera
	 *@param r for belonging of current frame to Camera class.
	 **/
	void setAsCameraFrame(bool r);

	/**
	   * @brief Flag current frame as having changed since last update
	   * @param r for flagging frame as needing update
	   **/
	void setUpdate(bool r);

	/**
	   * @brief Return true if current frame has changed since last update
	   * @return true if current frame has changed since last update
	   **/
	bool updateNeeded();

	std::vector< Frame*> m_Sons; // Vector of frames attached to this one
private:
	glm::mat4 matrix; ///< 4x4 matrix defining frame transformation
	bool isCamera;  ///< boolean flagging current frame as belonging to instance of Camera class
	Frame *reference; ///< Father frame.
	bool m_ToUpdate;/// set to true when the frame change
};








#endif
