-module(pacman).
-export([getMaxPacgums/0]).
%-export([findMostPacgums/3]).


getNumberOfMoves({ok, [N]}) ->
	N;

getNumberOfMoves(_) ->
	invalid_number_of_moves.



parseLine([$X | Tail]) ->
	[wall | parseLine(Tail)];

parseLine([$C | Tail]) ->
	[pacman | parseLine(Tail)];

parseLine([$O | Tail]) ->
	[warp | parseLine(Tail)];

parseLine([String | Tail]) ->
	Integer = case string:to_integer([String]) of
			{Int, _} ->
				  Int;
			  _ ->
				  0
		  end,
	[Integer | parseLine(Tail)];

parseLine(_) ->
	[].


getFields(eof) ->
	%io:format("Get Fields empty~n", []),
	%io:format(standard_error, "EOF", []),
	[];

getFields({error, Info}) ->
	io:format("Get Fields error: ~p~n", [Info]);
	%io:format(standard_error, "Erros~n", []).

getFields(Line) ->
	%io:format("Get Fields line read~n", []),
	%io:format(standard_error, "~s~n", [Line]),
	LineLen = string:len(Line) - 1,
	LineInAtoms = parseLine(string:left(Line, LineLen)),
	[LineInAtoms | getFields()].


getFields() ->
	%io:format(standard_error, "Get", []),
	getFields(io:get_line("")).


handleNumberOfMoves(invalid_number_of_moves) ->
	void;

handleNumberOfMoves(_) ->
	getFields().


findPacmanInRow([], _) ->
	not_found;

findPacmanInRow([pacman | Row], N) ->
	N;

findPacmanInRow([Col | Row], N) ->
	findPacmanInRow(Row, N + 1).


findPacman([], N) ->
	not_found;

findPacman([Row | Fields], N) ->
	case findPacmanInRow(Row, 1) of
		not_found ->
			findPacman(Fields, N + 1);
		X -> 
			{N, X}
	end.


getFieldValue({X, Y}, Fields) ->
	io:format("Field: ~p:~p = ~p~n", [X, Y, lists:nth(X ,lists:nth(Y, Fields))]),
	case lists:nth(X ,lists:nth(Y, Fields)) of
		pacman ->
			0;
		wall ->
			0;
		warp ->
			0;
		N ->
			N
	end.


move(down, {X, Y}, Fields) ->
	NewPacmanPos = {X, Y + 1},
	NewFields = Fields,
	{NewFields, NewPacmanPos}.


getMostPacgumsWhenGoUp(N, Fields, PacmanPos) ->
	{NewFields, NewPacmanPos} = move(down, PacmanPos, Fields),
	io:format("Pacman: ~p~n", [NewPacmanPos]),
	getFieldValue(NewPacmanPos, Fields) + findMostPacgums(N - 1, Fields).


findMostPacgums(0, _) ->
	0;

findMostPacgums(N, Fields) ->
	PacmanPos = findPacman(Fields, 1),
	io:format("Pacman: ~p~n", [PacmanPos]),
	getMostPacgumsWhenGoUp(N, Fields, PacmanPos).


getMaxPacgums() ->
	N = getNumberOfMoves(io:fread("", "~d")),
	io:format("Number of moves: ~p~n", [N]),
	Fields = handleNumberOfMoves(N),
	io:format("Readed fields: ~p~n", [Fields]),
	MostPacgums = findMostPacgums(N, Fields),
	io:format("Most pacgums: ~p~n", [MostPacgums]).

