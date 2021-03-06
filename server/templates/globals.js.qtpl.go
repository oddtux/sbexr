// This file is automatically generated by qtc from "globals.js.qtpl".
// See https://github.com/valyala/quicktemplate for details.

//line globals.js.qtpl:1
package templates

//line globals.js.qtpl:1
import "github.com/ccontavalli/sbexr/server/structs"

//line globals.js.qtpl:3
import (
	qtio422016 "io"

	qt422016 "github.com/valyala/quicktemplate"
)

//line globals.js.qtpl:3
var (
	_ = qtio422016.Copy
	_ = qt422016.AcquireByteBuffer
)

//line globals.js.qtpl:3
func StreamGlobalsJs(qw422016 *qt422016.Writer, data structs.JNavData) {
	//line globals.js.qtpl:3
	qw422016.N().S(` var globalTag = "`)
	//line globals.js.qtpl:4
	qw422016.E().S(data.Tag)
	//line globals.js.qtpl:4
	qw422016.N().S(`"; var globalProject = "`)
	//line globals.js.qtpl:5
	qw422016.E().S(data.Project)
	//line globals.js.qtpl:5
	qw422016.N().S(`"; var globalRoot = "`)
	//line globals.js.qtpl:6
	qw422016.E().S(data.Root)
	//line globals.js.qtpl:6
	qw422016.N().S(`"; var globalServerTags = [`)
	//line globals.js.qtpl:7
	for _, tag := range data.Tags {
		//line globals.js.qtpl:7
		qw422016.N().S(`"`)
		//line globals.js.qtpl:7
		qw422016.E().J(tag)
		//line globals.js.qtpl:7
		qw422016.N().S(`",`)
		//line globals.js.qtpl:7
	}
	//line globals.js.qtpl:7
	qw422016.N().S(`];`)
//line globals.js.qtpl:7
}

//line globals.js.qtpl:7
func WriteGlobalsJs(qq422016 qtio422016.Writer, data structs.JNavData) {
	//line globals.js.qtpl:7
	qw422016 := qt422016.AcquireWriter(qq422016)
	//line globals.js.qtpl:7
	StreamGlobalsJs(qw422016, data)
	//line globals.js.qtpl:7
	qt422016.ReleaseWriter(qw422016)
//line globals.js.qtpl:7
}

//line globals.js.qtpl:7
func GlobalsJs(data structs.JNavData) string {
	//line globals.js.qtpl:7
	qb422016 := qt422016.AcquireByteBuffer()
	//line globals.js.qtpl:7
	WriteGlobalsJs(qb422016, data)
	//line globals.js.qtpl:7
	qs422016 := string(qb422016.B)
	//line globals.js.qtpl:7
	qt422016.ReleaseByteBuffer(qb422016)
	//line globals.js.qtpl:7
	return qs422016
//line globals.js.qtpl:7
}
