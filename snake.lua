scriptId = 'com.thalmic.examples.outputeverything'
scriptTitle = "Output Everything"
scriptDetailsUrl = "" -- We don't have this until it's submitted to the Myo Market

function onPoseEdge(pose, edge)
	myo.unlock("hold")
    myo.debug("onPose: " .. pose.. " edge:"..edge)
    if(pose == "waveOut")then
    	if(edge == "on")then
	    	myo.keyboard("d","press")
	    	myo.keyboard("return","press")
    	elseif(edge == "off")then
    	end

    elseif(pose == "waveIn")then
    	if(edge == "on")then
	    	myo.keyboard("a","press")
	    	myo.keyboard("return","press")
    	elseif(edge == "off")then
    	end

    elseif(pose == "fist")then
    	if(edge == "on")then
	    	myo.keyboard("w","press")
	    	myo.keyboard("return","press")
    	elseif(edge == "off")then
    	end

    elseif(pose == "fingersSpread")then
    	if(edge == "on")then
	    	myo.keyboard("s","press")
	    	myo.keyboard("return","press")
    	elseif(edge == "off")then
    	end

    elseif(pose == "doubleTap")then
    	if(edge == "on")then
	    	myo.keyboard("x","press")
	    	myo.keyboard("return","press")
    	elseif(edge == "off")then
    	end
    end
end

function onPeriodic()
end

function onForegroundWindowChange(app, title)
    myo.debug("onForegroundWindowChange: " .. app .. ", " .. title)
    return true
end

function activeAppName()
    return "Output Everything"
end

function onActiveChange(isActive)
    myo.debug("onActiveChange")
end