import{ls as t}from"../platform/platform.js";import{Runtime as e}from"../root/root.js";import{ViewManager as i}from"../ui/ui.js";let n;i.registerViewExtension({location:"drawer-view",id:"Inputs",title:()=>t`Inputs`,commandPrompt:"Show Inputs",persistence:"closeable",order:7,loadView:async()=>(await async function(){return n||(await e.Runtime.instance().loadModulePromise("input"),n=await import("./input.js")),n}()).InputTimeline.InputTimeline.instance(),experiment:e.ExperimentName.TIMELINE_REPLAY_EVENT});
