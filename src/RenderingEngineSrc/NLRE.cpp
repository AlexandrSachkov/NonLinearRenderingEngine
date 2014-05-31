/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

Copyright (c) 2014 NonLinear Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "stdafx.h"
#include "RenderingEngine\NLRE.h"

NLRE::NLRE(HWND hwndVal, int widthVal, int heightVal){
	_deviceController.reset(new NLREDeviceController(hwndVal, widthVal, heightVal, NLRE_RENDERING_TECHNIQUE_ID::NLRE_FORWARD_RT));
	_renderingDevice = _deviceController->getRenderingDevice();
	_textureLoader.reset(new NLRETextureLoader(_renderingDevice));
	_sceneManager.reset(new NLRESceneManager(_deviceController, _renderingDevice, _textureLoader, widthVal, heightVal));
	_assetImporter.reset(new NLREAssetImporter(_renderingDevice, _textureLoader));
}

NLRE::~NLRE(){

}

void NLRE::render()
{
	_sceneManager->render();
}

void NLRE::importAsset(std::wstring path)
{
	std::vector<std::shared_ptr<NLRE_RenderableAsset>> assets;
	std::string strPath(path.begin(), path.end());
	if (_assetImporter->importAssets(path, assets))
	{
		NLRE_Log::console("Successfully imported asset at: %s", strPath.c_str());
		NLRE_Log::console("Number of items in the asset vector: %i", assets.size());
		_sceneManager->addAssets(assets);
	}
}

std::shared_ptr<NLREAssetImporter> NLRE::getAssetImporter()
{
	return _assetImporter;
}

std::shared_ptr<NLRESceneManager> NLRE::getSceneManager()
{
	return _sceneManager;
}