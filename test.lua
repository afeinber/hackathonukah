scriptId = 'com.thalmic.examples.outputeverything'
scriptTitle = "Output Everything"
scriptDetailsUrl = "" -- We don't have this until it's submitted to the Myo Market

function onPoseEdge(pose, edge)

    myo.debug("onPose: " .. pose)
    if(pose == "waveOut")then
    	myo.keyboard("d","press")
    	myo.keyboard("return","press")

    elseif(pose == "waveIn")then
    	myo.keyboard("a","press")
    	myo.keyboard("return","press")

    elseif(pose == "fist")then
    	myo.keyboard("w","press")
    	myo.keyboard("return","press")

    elseif(pose == "fingersSpread")then
    	myo.keyboard("s","press")
    	myo.keyboard("return","press")

    elseif(pose == "doubleTap")then
    	myo.keyboard("x","press")
    	myo.keyboard("return","press")
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